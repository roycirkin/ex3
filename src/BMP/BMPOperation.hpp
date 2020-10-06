#pragma once
#include "../CacheManager.hpp"
#include <string>
#include <fstream>

namespace BMPOperation {

    enum bmpOperations {
        convertToGrayScale, rotateImage,
    };

void bmpOperation(const std::string& inputFile, const std::string& outputFile,
cacheManager::CacheManager& cache, bmpOperations m);








}