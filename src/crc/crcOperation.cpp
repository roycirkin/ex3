#include "crcOperation.hpp"
#include "../BMP/Exceptions.hpp"
#include <string>
#include <ostream>
#include <sstream>
#include <fstream>
#include <ostream>
#include <iostream>

namespace CRCoperation {



uint32_t getCRC(const std::string& buffer) {
    return calculate_crc32c(0, (const unsigned char*) buffer.c_str(), buffer.length());
}

void crcTask(std::istream& instream, std::ostream& outStream) {
    std::stringstream buffer;
    char c;
    while (instream.get(c)) {
        buffer << c;
    }
    uint32_t result = getCRC(buffer.str());
    outStream << result;
}

void crcOperationManage(std::string& inFile, std::string& outFile, cacheManager::CacheManager cache) {

 
    std::ostream * pout;
    std::ofstream oFile;
    
    if (outFile != "stdout") {
        oFile.open(outFile, std::ios::out | std::ios::trunc);
        if (!oFile.is_open()) {
            throw FileExceptions::OpenFileExceptionForReading();
        }
        pout = &oFile;
    } else  {
        pout = &(std::cout);
    }

    std::ifstream inputFile(inFile, std::ios::in | std::ios::binary);

    std::stringstream ss;
    ss << "hash_crc32";
    char c;
    while (inputFile.get(c)) {
        ss << c;
    }

    std::string key = ss.str();
    std::string val;
    bool res = cache.searchKey(key, val);
    if (res) {
        pout->write(val.c_str(), val.length());
    } else {

        std::ifstream istr(inFile, std::ios::in | std::ios::binary);
        std::stringstream sscrc;
        crcTask(istr, sscrc);
        pout->write(sscrc.str().c_str(), sscrc.str().length());
        crcTask(istr, sscrc);
        val = sscrc.str();
        cache.insert(key, val);
    }

    oFile.close();
}





}