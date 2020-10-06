#pragma once
#include <unistd.h>
#include <string>
#include "crc32c.h"
#include "../CacheManager.hpp"
#



namespace CRCoperation {

//0
//char*
//length
uint32_t getCRC(char* parameter);

void crcTask(std::istream& instream, std::ostream& outStream);

void crcOperationManage(std::string& inFile, std::string& outFile, cacheManager::CacheManager cache);










}