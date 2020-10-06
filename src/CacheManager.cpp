#include "CacheManager.hpp"
#include "FileNode.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <ctime>
#include <chrono>
#include "BMP/Exceptions.hpp"
#include "matrix/ClassMatrix.hpp"
#include "matrix/MatrixParser.hpp"


namespace cacheManager {

const size_t sizeOfHashInFileName = 16;

size_t CacheManager::getHash(const std::string& str) {
    std::hash<std::string> hashfn;
    auto hash = hashfn(str);
    return hash;
}

CacheManager::CacheManager(std::filesystem::path & workdir) : m_workdir(workdir)
{}

void CacheManager::insert(const std::string& key, const std::string& val) {
    size_t hash = getHash(key);
    std::stringstream ss;

    std::stringstream bucketChecker;
    size_t bucket = 0;
    std::vector<FileNode>::iterator iter;
    bucketChecker << std::setfill('0')<<std::setw(sizeof(hash)*2)<<std::hex<<hash;
    std::string hashKey = bucketChecker.str();

    //calculating the new file bucket
    for (iter = m_lru.begin(); iter != m_lru.end(); ++iter) {
        if (hash == iter->getKeyHash()) {
            //first 1 is the length of h and the second 1 is the length of _
            std::string fileName =  iter->getFileName().filename();
            std::string bucketTemp = fileName.substr(1 + sizeOfHashInFileName + 1);
            size_t dot_pos = bucketTemp.find(".");
            bucketTemp = bucketTemp.substr(0,dot_pos);
            std::stringstream ssbucket(bucketTemp);
            size_t currentBucket = 0;
            ss >> currentBucket;
            if (currentBucket > bucket) {
                bucket = currentBucket + 1;
            }
        }
    }

    ss<<'h'<<std::setfill('0')<<std::setw(sizeof(hash)*2)<<std::hex<<hash<<'_'<<bucket<<".cache";
    std::filesystem::path fileName = m_workdir / std::filesystem::path(ss.str());
    size_t sizeOfFile = sizeof(CacheNode) + key.length() + val.length();
    auto tp = std::chrono::system_clock::now();

    FileNode newNode(tp, tp, 0, sizeOfFile, key.length(), val.length(), hash, fileName);

    m_lru.push_back(newNode);
    this->sortLRU();
    if (m_lru.size() > sizeOfCache)
    {
        manageCacheCapacity();
    }

    newNode.write(key, val, hash);
}

bool CacheManager::searchKey(const std::string& key, std::string& val) {

    auto hash = getHash(key);
    std::vector<FileNode>::iterator iter;
    std::stringstream ss;
    ss<<std::setfill('0')<<std::setw(sizeof(hash)*2)<<std::hex<<hash;
    std::string keyHash = ss.str();

    for(iter = m_lru.begin(); iter != m_lru.end(); ++iter) {
        if (hash == iter->getKeyHash()) {

            std::string cahched_key;
            iter->readKey(cahched_key);

            if (cahched_key == key) {
                
                iter->setHitCounter(iter->getHitCounter() + 1);
                auto tp = std::chrono::system_clock::now();
                iter->setLastUsed(tp);
                iter->updateFile(*iter);
                iter->readVal(val);
                this->sortLRU();
                return true;
            }
        }
    }
    return false;
}

void CacheManager::manageCacheCapacity() {

    if (m_lru.size() > sizeOfCache) { 
        std::filesystem::path fileName = m_lru.back().getFileName();
        std::filesystem::remove(fileName);
        m_lru.pop_back();
    }
}

void CacheManager::sortLRU() {
    std::sort(m_lru.begin(), m_lru.end());
}

void CacheManager::rebuildLRU() {

    for (auto& f: std::filesystem::directory_iterator(m_workdir)) {
        if (f.is_regular_file()) {
            std::ifstream file(f.path(), std::ios::in | std::ios::binary);
            FileNode fileNodeReader(f.path());
            CacheNode cacheNode;
            fileNodeReader.readCacheNode(cacheNode);
            FileNode fileNode(cacheNode, f.path());
            m_lru.push_back(fileNode);
        }
    }



}

FileNode CacheManager::getNamedCacheNodeFromFile(std::istream& file, std::string fileName) {
    CacheNode temp;
    file >> temp;
    FileNode newNode(temp, fileName);
    return newNode;

}

void CacheManager::clearCache() {
    for (auto& f: std::filesystem::directory_iterator(m_workdir)) {
        //regex that will do it only to files which are validate (h+hash+_...)
        if (f.is_regular_file()) {
            std::filesystem::remove(f.path());
        }
    }
}

std::chrono::time_point<std::chrono::system_clock> CacheManager::getSavedTime(const std::string& key) {
    
    auto hash = getHash(key);
    std::vector<FileNode>::iterator iter;
    std::stringstream ss;
    ss<<std::setfill('0')<<std::setw(sizeof(hash)*2)<<std::hex<<hash;
    std::string keyHash = ss.str();

    for(iter = m_lru.begin(); iter != m_lru.end(); ++iter) {
        if (hash == iter->getKeyHash()) {

            std::vector<char> cahched_key_vetor;

            std::string cahched_key;
            iter->readKey(cahched_key);

            if (cahched_key == key) {
                return iter->getSavedTime();
            }
        }
    }
    throw CantFindSavedTimeException();
    iter = m_lru.begin();
    return iter->getSavedTime();
}








}
    