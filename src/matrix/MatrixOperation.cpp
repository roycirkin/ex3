#include "MatrixParser.hpp"
#include "MatrixOperation.hpp"
#include "ClassMatrix.hpp"
#include "../BMP/Exceptions.hpp"
#include "MatrixParser.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>


namespace MatrixOperation {


void matOperation(const std::string& inputFile1, const std::string& inputFile2,const std::string& outputFile,
cacheManager::CacheManager& cache, matrixOperation m) {

    std::ostream * pout;
    std::ofstream oFile;
    
    if (outputFile != "stdout") {
        oFile.open(outputFile, std::ios::out | std::ios::trunc);
        if (!oFile.is_open()) {
            throw FileExceptions::OpenFileExceptionForReading();
        }
        pout = &oFile;
    } else  {
        pout = &(std::cout);
    }

    std::unique_ptr<matrix::Matrix> input1 = std::make_unique<matrix::Matrix>(MatrixParsering::getMatrixFromFile(inputFile1));
    std::unique_ptr<matrix::Matrix> input2 = std::make_unique<matrix::Matrix>(MatrixParsering::getMatrixFromFile(inputFile2));

    std::stringstream ss;
    if (m == add) {
    ss << "matrix_add" << *(input1.get()) << *(input2.get());
    } else if (m == multiply){
    ss << "matrix_multiply" << *(input1.get()) << *(input2.get());
    } else {
        std::cerr << "no such task";
        return;
    }

    std::string key = ss.str();
    std::string val;
    bool res = cache.searchKey(key, val);
    if (res) {

        pout->write(val.c_str(), val.length());
        pout->flush();
        
    } else {

        matrix::Matrix output(input1.get()->matrixGetHeight(), (input2.get())->matrixGetWidth());
        if (m == add) {
            output = *(input1.get()) + (*(input2.get()));
        } else if (m == multiply) {
            output = *(input1.get()) * (*(input2.get()));
        } else {
            std::cerr << "no such task";
            return;
        }
        
        *pout << output;
        std::stringstream ss2;
        ss2 << output;
        val = ss2.str();
        cache.insert(key, val);
        
    }

    oFile.close();
    
}



}