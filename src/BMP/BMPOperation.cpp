#include "BMPOperation.hpp"
#include "bmp_tester.hpp"
#include "Exceptions.hpp"
#include <iostream>
#include <ostream>
#include <filesystem>


namespace BMPOperation {

void bmpOperation(const std::string& inputFile, const std::string& outputFile,
cacheManager::CacheManager& cache, bmpOperations m) {

    std::ostream* pout;
    std::fstream oFile;
    
    oFile.open(outputFile, std::ios::out | std::ios::trunc | std::ios::in);
    if (!oFile.is_open()) {
        throw FileExceptions::OpenFileExceptionForReading();
    }
    pout = &oFile;

    std::ifstream input;
    input.open(inputFile, std::ios::in | std::ios::binary);
    if (!input.is_open()) {
        throw FileExceptions::ReadFileException();
    }


    std::stringstream ss;
    if (m == convertToGrayScale) {
        ss << "image_convert";
        char c;
        while (input.get(c)) {
            ss << c;
        }
    
    } else if (m == rotateImage) {
        ss << "image_rotate";
        char c;
        while (input.get(c)) {
            ss << c;
        }

    } else {
        std::cerr << "no such task";
        return;
    }

    std::string key = ss.str();
    std::string val;
    bool res = cache.searchKey(key, val);
    if (res) {
        *pout << val;
    } else {
        
        if (m == convertToGrayScale) {
            testing::bmp::convert_to_grayscale(inputFile, outputFile);
        } else if (m == rotateImage) {
            testing::bmp::rotate_image(inputFile, outputFile);
        } else {
            std::cerr << "no such task";
            return;

        }
        std::ifstream outFile(outputFile, std::ios::in);
        char c;
        std::stringstream reader;

        while (outFile.get(c)) {
            reader << c;
        }
        val = reader.str();
        cache.insert(key, val);
    }

    oFile.close();
    input.close();

}


}