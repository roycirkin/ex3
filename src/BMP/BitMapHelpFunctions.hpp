#include "Headers.hpp"
#include "BitMap.hpp"
#include <vector>


namespace BMPFunctions {
    /**
     * @brief  creates a black and white color pallete
     *
     * @param pallete the pallete
    */
    void getBlackAndWhitePallete(std::vector<Headers::colorTupple>& pallete);

    /**
     * @brief initialize a new 8BitMap file header
     *
     * @param theNewHeader the new header
     * @param bitMap a pointer to the pevious bitMap
     * @param theNewPallete his new pallete
     * @param theNewBitMapArray the new bit map array
    */
    void init8BitsBMPHeader(Headers::Header& theNewHeader, BitMap::BitMapAbstract* bitMap,
    std::vector<Headers::colorTupple>& theNewPallete, std::vector<uint8_t>& theNewBitMapArray);

    /**
     * @brief initialize a new 8BitMap file DIBheader
     *
     * @param theNewDIBHeader the new DIBheader
     * @param bitMap a pointer to the pevious bitMap
    */
    void init8BitsBMP_DIBHeader(Headers::DIBHeader& theNewDIBHeader, BitMap::BitMapAbstract* bitMap);


}