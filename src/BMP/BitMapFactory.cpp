
#include "BitMapFactory.hpp"
#include "Headers.hpp"
#include "Exceptions.hpp"
#include <iostream>
#include <fstream>
namespace Factory{

    BitMap::BitMapAbstract* BitMapFactory::fromFile(const std::string& imagePath){

        std::ifstream imageFile;
        imageFile.open(imagePath, std::ios::in);
        if (imageFile.fail()) {
           throw FileExceptions::OpenFileExceptionForReading();
        }

        Headers::Header header;
        Headers::DIBHeader dibInfo;
        
        header.fromfStream(imageFile);
        dibInfo.fromfStream(imageFile);

        size_t bitsPerPixel = dibInfo.bitesPerPixel;
        BitMap::BitMapAbstract* bitMap = nullptr;

        if (bitsPerPixel == 8) {
            bitMap = new BitMap::BitMap8Bits(header, dibInfo);
        } else if (bitsPerPixel == 24) {
            bitMap = new BitMap::BitMap24Bits(header, dibInfo);
        } else {
            throw FileExceptions::WrongBMPFileException();
        }
        
        bitMap->fromFile(imageFile);
        imageFile.close();
        return bitMap;

    }
}