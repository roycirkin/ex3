#pragma once
#include "BitMap.hpp"
#include <memory>

namespace Factory{
class BitMapFactory {
public:
    /**
     * @brief reading the needed information from the file to decide either to create 
     * an 8 bits bmp or to create a 24 bits one
     *
     * @param imagePath the bm file of our object
     * @return a pointer to the new created object
    */
    static BitMap::BitMapAbstract* fromFile(const std::string& imagePath);
};

}