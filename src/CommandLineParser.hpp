#pragma once
#include <iostream>


namespace commandLineParser {

class Operation {
public:
    enum Operations_enum 
    { 
        addMatrixOperation, 
        multiplyMatrixOperation, 
        convertToGrayScale, 
        rotateImage, 
        crc32Operation,
        clearCache, 
        noSuchOperation,
        searchInCacheOneInput,
        searchInCacheMatrix,
    };

    static Operation::Operations_enum getOperation (int argc, char** argv);

};




}