#pragma once
#include "CacheList.hpp"
#include "CommandLineParser.hpp"
#include "FileNode.hpp"
#include <vector>
#include <filesystem>
#include <time.h>
#include <chrono>
#include <iostream>



namespace cacheManager{

class CacheManager{
    
    private:
    std::vector<FileNode> m_lru;
    size_t sizeOfCache = 3;

    std::filesystem::path m_workdir;
    
    public:
    CacheManager(std::filesystem::path &workdir);

    void insert(const std::string& key, const std::string& val);

    //last recently used
    void sortLRU();

    bool searchKey(const std::string& key, std::string& val) ;

    //rebuilding the lru from the files in the cache
    void rebuildLRU();

    static size_t getHash(const std::string& str) ;

    void manageCacheCapacity(); 

    FileNode getNamedCacheNodeFromFile(std::istream& file, std::string fileName);

    void clearCache();

    std::chrono::time_point<std::chrono::system_clock> getSavedTime(const std::string& key);

    // bool searchOperationInCache(const std::string& key);
};

class CantFindSavedTimeException {
    public:
    void print() {
        std::cerr << "cant find the save time";
    }
};



}