#include "BitMapHelpFunctions.hpp"
#include "Headers.hpp"
#include "BitMap.hpp"

namespace BMPFunctions{

void getBlackAndWhitePallete(std::vector<Headers::colorTupple>& pallete) {

    for (size_t i = 0; i < pallete.size(); ++i) {
        pallete[i].red = i;
        pallete[i].green = i;
        pallete[i].blue = i;
    }

}


void init8BitsBMPHeader(Headers::Header& theNewHeader, BitMap::BitMapAbstract* bitMap,
std::vector<Headers::colorTupple>& theNewPallete, std::vector<uint8_t>& theNewBitMapArray) {

    theNewHeader.signature = Headers::BMPmagic;
    theNewHeader.sizeOfFile = sizeof(Headers::Header) + sizeof(Headers::DIBHeader) 
    + theNewPallete.size() * sizeof(Headers::colorTupple) + theNewBitMapArray.size();
    theNewHeader.reserved1 = bitMap->getHeader().reserved1;
    theNewHeader.reserved2 = bitMap->getHeader().reserved2;
    theNewHeader.offsetPixelArray = sizeof(Headers::Header) + sizeof(Headers::DIBHeader)
    + theNewPallete.size() * sizeof(Headers::colorTupple);

}

void init8BitsBMP_DIBHeader(Headers::DIBHeader& theNewDIBHeader, BitMap::BitMapAbstract* bitMap) {

    theNewDIBHeader.sizeOfHeader = Headers::Size0fDIBHeader;
    theNewDIBHeader.height = bitMap->getDIBHeader().height;
    theNewDIBHeader.width = bitMap->getDIBHeader().width;
    theNewDIBHeader.bitesPerPixel = 8;
    theNewDIBHeader.compressionIndex1 = bitMap->getDIBHeader().compressionIndex1;
    theNewDIBHeader.compressionIndex2 = bitMap->getDIBHeader().compressionIndex2;
    theNewDIBHeader.reserved1 = bitMap->getDIBHeader().reserved1;
    theNewDIBHeader.reserved2 = bitMap->getDIBHeader().reserved2;
    theNewDIBHeader.colorsInColorPallete = 0;
    theNewDIBHeader.reserved3 = bitMap->getDIBHeader().reserved3;

}




}