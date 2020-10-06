#pragma once
#include "CacheList.hpp"
#include <filesystem>
#include <string>
#include <chrono>
#include <time.h>

namespace cacheManager {

class FileNode : public CacheNode{
private:
    std::filesystem::path m_fileName;
public:
    void readCacheNode(CacheNode & cahceNode);
    void readKey(std::string& key) const;
    void readVal(std::string& val) const;
    size_t getSize() const;
    void write(const std::string& key, const std::string& val, size_t keyHash);
    void updateFile(CacheNode& cahceNode);
    const std::filesystem::path getFileName() const;

    FileNode(std::chrono::time_point<std::chrono::system_clock>  lastUsed, std::chrono::time_point<std::chrono::system_clock> savedTime, 
            size_t hitCounter,  size_t sizeInBytes, size_t keySizeInBytes, size_t valSizeInBytes,
            size_t key_hash, std::filesystem::path& fileName);
    FileNode();
    FileNode(CacheNode& node, const std::filesystem::path& fileName);
    FileNode(const std::filesystem::path& fileName);


};



}