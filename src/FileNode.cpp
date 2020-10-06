#include "FileNode.hpp"
#include "CacheList.hpp"
#include "BMP/Exceptions.hpp"
#include <fstream>
#include <vector>

namespace cacheManager {


FileNode::FileNode(const std::filesystem::path& fileName) : m_fileName(fileName){}

void FileNode::write(const std::string& key, const std::string& val, size_t keyHash) {

    std::ofstream file(m_fileName, std::ios::out | std::ios::binary | std::ios::trunc);
    if(!file.is_open()) {
        throw FileExceptions::OpenFileExceptionForReading();
    }

    auto tp = std::chrono::system_clock::now();
    cacheManager::CacheNode cachenode(tp, tp, 0, sizeof(cachenode) + key.length() + val.length(),
    key.length(), val.size(), keyHash);


    file << cachenode;

    file.write(key.c_str(), key.length());
    file.write(val.c_str(), val.length());
    file.close();
}


void FileNode::readVal(std::string& val) const {
    std::ifstream file(m_fileName, std::ios::in | std::ios::binary);
    CacheNode cahceNode;
    if(!file.is_open()) {
        throw FileExceptions::OpenFileExceptionForReading();
    }

    file>>cahceNode;
    
    if (!file.seekg(cahceNode.getKeySize() + sizeof(CacheNode))) {
        throw FileExceptions::ReadFileException();
    }
    std::vector<char> vec;
    vec.resize(cahceNode.getValSize());
    if (!file.read(&vec[0], cahceNode.getValSize())) {
        throw FileExceptions::ReadFileException();
    }
    val = std::string(vec.begin(), vec.end());
    file.close();
}

void FileNode::readKey(std::string& key) const {
    std::ifstream file(m_fileName, std::ios::in | std::ios::binary);
    CacheNode cahceNode;
    if(!file.is_open()) {
        throw FileExceptions::OpenFileExceptionForReading();
    }

    file>>cahceNode;

    std::vector<char> vec(cahceNode.getKeySize());
    if (!file.read((char*)&vec[0], cahceNode.getKeySize())) {
        throw FileExceptions::ReadFileException();
    }
    key = std::string(vec.begin(), vec.end());
    file.close();
}

void FileNode::readCacheNode(CacheNode & cahceNode) {
    std::ifstream file(m_fileName, std::ios::in | std::ios::binary);
    if(!file.is_open()) {
        throw FileExceptions::OpenFileExceptionForReading();
    }

    file>>cahceNode;
    if(!file) {
        throw FileExceptions::ReadFileException();
    }
    file.close();
}

void FileNode::updateFile(CacheNode& cacheNode) {
    std::ofstream file(m_fileName, std::ios_base::in | std::ios::out | std::ios::binary );
    if(!file.is_open()) {
        throw FileExceptions::OpenFileExceptionForReading();
    }
    
    file<<cacheNode;
    file.close();
}

const std::filesystem::path FileNode::getFileName() const{
    return m_fileName;
}

FileNode::FileNode(
    std::chrono::time_point<std::chrono::system_clock>  lastUsed,
    std::chrono::time_point<std::chrono::system_clock> savedTime, 
    size_t hitCounter, 
    size_t sizeInBytes,
    size_t keySizeInBytes,
    size_t valSizeInBytes,
    size_t key_hash,
    std::filesystem::path& fileName) : CacheNode(lastUsed, savedTime, hitCounter, sizeInBytes, 
    keySizeInBytes, valSizeInBytes, key_hash), m_fileName(fileName)

{}

FileNode::FileNode() {}

FileNode::FileNode(CacheNode& node, const std::filesystem::path& fileName) : CacheNode(node), m_fileName(fileName) {}



}

