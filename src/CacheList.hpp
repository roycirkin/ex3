#pragma once
#include <string>
#include <ctime>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <stdlib.h>


namespace cacheManager {

class CacheNode {

    private:
        std::chrono::time_point<std::chrono::system_clock>  m_lastUsed;
        std::chrono::time_point<std::chrono::system_clock>  m_savedTime;
        size_t m_hitCounter;
        size_t m_sizeInBytes;
        size_t m_keySizeInBytes;
        size_t m_valSizeInBytes;
        size_t m_key_hash;
    public:


        CacheNode();

        CacheNode(
            std::chrono::time_point<std::chrono::system_clock>  lastUsed,
            std::chrono::time_point<std::chrono::system_clock> savedTime, 
            size_t hitCounter, 
            size_t sizeInBytes,
            size_t keySizeInBytes,
            size_t valSizeInBytes,
            size_t key_hash);


        std::chrono::time_point<std::chrono::system_clock> getSavedTime() const;
        void setSavedTime(const std::chrono::time_point<std::chrono::system_clock> savedTime);
        size_t getHitCounter() const;
        void setHitCounter(const size_t hitCounter);
        std::chrono::time_point<std::chrono::system_clock>  getLastUsed() const;
        void setLastUsed(const std::chrono::time_point<std::chrono::system_clock> lastUsed);
        size_t getSize() const;
        void setSize(const size_t size);
        size_t getKeySize() const;
        size_t getValSize() const;
        size_t getKeyHash() const;

        bool operator<(CacheNode& other) const;
};


std::ostream& operator<<(std::ostream& ostr,const cacheManager::CacheNode& cacheNode);
std::istream& operator>>(std::istream& istr, cacheManager::CacheNode& cacheNode);
}