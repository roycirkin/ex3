#include "CacheList.hpp"
#include <cstring>


namespace cacheManager {

std::chrono::time_point<std::chrono::system_clock>  CacheNode::getSavedTime() const 
{
    return m_savedTime;
}

void CacheNode::setSavedTime(const std::chrono::time_point<std::chrono::system_clock> savedTime)
{
    m_savedTime = savedTime;
}

size_t CacheNode::getHitCounter() const 
{
    return m_hitCounter;

}
void CacheNode::setHitCounter(const size_t hitCounter)
{
    m_hitCounter = hitCounter;
}

std::chrono::time_point<std::chrono::system_clock>  CacheNode::getLastUsed() const 
{
    return m_lastUsed;
}

void CacheNode::setLastUsed(const std::chrono::time_point<std::chrono::system_clock> lastUsed)
{
    m_lastUsed = lastUsed;
}

size_t CacheNode::getSize() const 
{
    return m_sizeInBytes;
}

void CacheNode::setSize(const size_t size)
{
    m_sizeInBytes = size;
}

CacheNode::CacheNode() : 
    m_hitCounter(0),
    m_sizeInBytes(0),
    m_keySizeInBytes(0),
    m_valSizeInBytes(0),
    m_key_hash(0)

{}

CacheNode::CacheNode(
            std::chrono::time_point<std::chrono::system_clock>  lastUsed,
            std::chrono::time_point<std::chrono::system_clock> savedTime, 
            size_t hitCounter, 
            size_t sizeInBytes,
            size_t keySizeInBytes,
            size_t valSizeInBytes,
            size_t key_hash):
    m_lastUsed(lastUsed),
    m_savedTime(savedTime),
    m_hitCounter(hitCounter),
    m_sizeInBytes(sizeInBytes),
    m_keySizeInBytes(keySizeInBytes),
    m_valSizeInBytes(valSizeInBytes),
    m_key_hash(key_hash)
    {}


bool CacheNode::operator<(CacheNode& other) const
{
    return m_lastUsed > other.getLastUsed();
}

size_t CacheNode::getKeySize() const{
        return m_keySizeInBytes;
}
size_t CacheNode::getValSize() const{
        return m_valSizeInBytes;
}
size_t CacheNode::getKeyHash() const{
    return m_key_hash;
}



std::ostream& operator<<(std::ostream& ostr,const cacheManager::CacheNode& cacheNode){
    ostr.write((char *)&cacheNode, sizeof(cacheNode));

    return ostr;
}

std::istream& operator>>(std::istream& istr,cacheManager::CacheNode& cacheNode){
    cacheManager::CacheNode newCacheNode;
    istr.read((char*)&newCacheNode, sizeof(CacheNode));
    if (istr) {
        cacheNode = newCacheNode;
    }
    return istr;
}



}


