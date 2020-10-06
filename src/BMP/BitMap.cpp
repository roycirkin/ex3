#include "BitMap.hpp"
#include "Exceptions.hpp"
#include "BitMapHelpFunctions.hpp"
#include <cstring>
namespace BitMap{
    //constructor
    BitMapAbstract::BitMapAbstract(const Headers::Header& headerInfo, const Headers::DIBHeader& DIBHeaderInfo)
    : m_headerInfo(headerInfo), m_DIBHeaderInfo(DIBHeaderInfo){}

    //constructor
    BitMapAbstract::BitMapAbstract(const Headers::Header& headerInfo,
    const Headers::DIBHeader& DIBHeaderInfo, ColorPalleteType& colorPallete,
    IntensityType& bitMapArray) : m_headerInfo(headerInfo), m_DIBHeaderInfo(DIBHeaderInfo),
    m_colorPallete(colorPallete), m_byteArray(bitMapArray){}

    //reading the info from the file
    void BitMapAbstract::fromFile(std::ifstream& imageFile) {
        size_t colorPalleteSize = 0;
        if (m_DIBHeaderInfo.colorsInColorPallete == 0) {
            colorPalleteSize = this->getColorPalleteSize();
        } else {
            colorPalleteSize = m_DIBHeaderInfo.colorsInColorPallete;
        }

        m_colorPallete.resize(colorPalleteSize);

        imageFile.read((char *) &m_colorPallete[0], colorPalleteSize * sizeof(Headers::colorTupple));
        if (!imageFile) {
            throw FileExceptions::ReadFileException();
        }

        auto width = this->getWidth();
        auto height = this->getHeight();
        auto bytesPerPixel = this->getBytesPerPIxel();

        m_byteArray.resize(height * width * bytesPerPixel);
        size_t peddingPerLine = 0;
        if (width % 4 != 0) {
            peddingPerLine = 4 - (width % 4);
        }

        for(size_t row = 0; row < height; ++row) {
            imageFile.read((char *) &m_byteArray[width * row * bytesPerPixel], width * bytesPerPixel);
            imageFile.seekg(peddingPerLine, std::ios_base::cur);
        }
    }

    //writing the info to the new file
    void BitMapAbstract::toFile(const std::string imagePath) {

        std::ofstream imageFile;
        imageFile.open(imagePath, std::ios::binary | std::ios::trunc);
        if (!imageFile.is_open()) {
           throw FileExceptions::ReadFileException();
        }

        if ((m_headerInfo.signature != Headers::BMPmagic) || (m_DIBHeaderInfo.sizeOfHeader != Headers::Size0fDIBHeader)) {
            throw FileExceptions::WrongBMPFileException();
        }
        //writing the headers and the collorPallete
        imageFile.write((char*) &m_headerInfo, sizeof(Headers::Header));
        imageFile.write((char*) &m_DIBHeaderInfo, sizeof(Headers::DIBHeader));
        auto collorPalleteSize = m_colorPallete.size();
        if (collorPalleteSize > 0) {
            imageFile.write((char*) &m_colorPallete[0], sizeof(Headers::colorTupple) * collorPalleteSize);
        }

        auto width = this->getWidth();
        auto height = this->getHeight();
        auto bytesPerPixel = this->getBytesPerPIxel();
        
        //max size of the pedding each line is 3 bytes
        const char pedding[3] = {0, 0, 0};
        auto peddingPerLine = 0;
        if (width % 4 != 0) {
            peddingPerLine = 4 - (width % 4);
        }
        //writing the bitMapArray
        for (size_t row = 0; row < height; ++row) {
            imageFile.write((char*) &m_byteArray[row * width * bytesPerPixel], width * bytesPerPixel);
            imageFile.write(pedding, peddingPerLine);
        } 
        imageFile.close();
    }

    void BitMapAbstract::setBitMapWidth(const uint32_t width){
        m_DIBHeaderInfo.width = width;
    }

    void BitMapAbstract::setBitMapHeight(const uint32_t height){
        m_DIBHeaderInfo.height = height;
    }

    void BitMapAbstract::rotate90Degrees() {
    
        IntensityType tempByteArray;
        tempByteArray.resize(m_byteArray.size());
        auto height = m_DIBHeaderInfo.height;
        auto width = m_DIBHeaderInfo.width;
        auto bytesPerPixel = m_DIBHeaderInfo.bitesPerPixel / 8;
        setBitMapHeight(width);
        setBitMapWidth(height);

        //rotating the matix of the pixels by 90 degrees
        //the calculations inside the for switch the locations of the pixels inside the matrix
        for (size_t row = 0; row < width; ++row) {
            for (size_t col = 0; col < height; ++col) {
                uint8_t* src = &m_byteArray[(col * width + width - row) * bytesPerPixel];
                uint8_t* des = &tempByteArray[(row * height + col) * bytesPerPixel];
                memcpy(des, src, bytesPerPixel);
            }
        }
        mempcpy(&m_byteArray[0], &tempByteArray[0], m_byteArray.size());
    }

    const Headers::Header& BitMapAbstract::getHeader() const{
        return m_headerInfo;
    }

    const Headers::DIBHeader& BitMapAbstract::getDIBHeader() const{
        return m_DIBHeaderInfo;
    }

    size_t BitMapAbstract::getHeight() const{
        return m_DIBHeaderInfo.height;
    }

    size_t BitMapAbstract::getWidth() const{
        return m_DIBHeaderInfo.width;
    }

    BitMapAbstract::ColorPalleteType& BitMapAbstract::getColorPallete() {
        return m_colorPallete;
    }

    size_t BitMapAbstract::getBytesPerPIxel() const {
        return m_DIBHeaderInfo.bitesPerPixel / 8;
    }

    BitMapAbstract::IntensityType& BitMapAbstract::getBitMapArray() {
        return m_byteArray;
    }

    uint8_t BitMapAbstract::getRGBToGray(const uint8_t blue, const uint8_t green, const uint8_t red) const {
        double result = (0.2126) * red + (0.7152) * green + (0.0722) * blue;
        return (uint8_t)result;
    }

    size_t BitMapAbstract::getColorPalleteSize() const {
        if (m_DIBHeaderInfo.bitesPerPixel == 8) {
            return BitMap8Bits::getColorPalleteSize();
        }
        if (m_DIBHeaderInfo.bitesPerPixel == 24) {
            return BitMap24Bits::getColorPalleteSize();
        }
        return 0;
    }



    BitMap8Bits::BitMap8Bits(const Headers::Header& header, const Headers::DIBHeader& dibHeader)
    :BitMapAbstract::BitMapAbstract(header, dibHeader){}

    size_t BitMap8Bits::getColorPalleteSize() {
        return m_ColorPalleteSize;
    }

    BitMap8Bits::BitMap8Bits(Headers::Header& theNewHeader, Headers::DIBHeader& theNewDIBHeader, ColorPalleteType& theNewPallete,
    IntensityType& theNewBitMapArray) : BitMapAbstract(theNewHeader, theNewDIBHeader, theNewPallete, theNewBitMapArray){}

    BitMap24Bits::BitMap24Bits(const Headers::Header& header, const Headers::DIBHeader& dibHeader)
    :BitMapAbstract::BitMapAbstract(header, dibHeader) {}

    size_t BitMap24Bits::getColorPalleteSize() {
        return m_ColorPalleteSize;
    }

    void BitMapAbstract::convertToGray(BitMap::BitMapAbstract* bitMap) {

        if (bitMap == nullptr) {
            throw FileExceptions::NULLPointerException();
        }

        if (bitMap->m_DIBHeaderInfo.bitesPerPixel == 8) {
            BitMap8Bits::convertToGray(bitMap);
        }

        if (bitMap->m_DIBHeaderInfo.bitesPerPixel == 24) {
            BitMap24Bits::convertToGray(bitMap);
        }
    }

    void BitMap8Bits::convertToGray(BitMap::BitMapAbstract* bitMap) {
        if (bitMap == nullptr || bitMap->getBytesPerPIxel() != 1) {
            throw FileExceptions::WrongBMPFileException();
        }

        ColorPalleteType& theNewColorPallete = bitMap->getColorPallete();
        if (theNewColorPallete.size() == 0) {
          throw FileExceptions::WrongBMPFileException();
        }
        //turning every collorTupple into gray
        for (Headers::colorTupple& c : theNewColorPallete) {
        auto result = bitMap->getRGBToGray(c.blue, c.green, c.red);
        c.blue = result;
        c.green = result;
        c.red = result;
        }
    }

    void BitMap24Bits::convertToGray(BitMap::BitMapAbstract* bitMap) {

        if (bitMap == nullptr || bitMap->getBytesPerPIxel() != 3) {
            throw FileExceptions::WrongBMPFileException();
        }

        auto colorPalleteSize8Bits = 256;
        auto height = bitMap->getHeight();
        auto width = bitMap->getWidth();
        auto bytesPerPixel = bitMap->getBytesPerPIxel	();
        IntensityType& BitmapArray = bitMap->getBitMapArray();

        //initializing the gray-scale color pallete
        ColorPalleteType theNewPallete;
        theNewPallete.resize(colorPalleteSize8Bits);
        BMPFunctions::getBlackAndWhitePallete(theNewPallete);

        //turning the bitmap  array into a 8 bits bitmapArray
        IntensityType theNewBitMapArray;
        theNewBitMapArray.resize(height * width);
        for (size_t row = 0; row < height ; ++row) {
            for (size_t col = 0; col < width * bytesPerPixel; col +=3) {
                auto blue = BitmapArray[(row * width) *  bytesPerPixel + col];
                auto green = BitmapArray[(row * width) * bytesPerPixel + col + 1];
                auto red = BitmapArray[(row * width) * bytesPerPixel + col + 2];

                auto result = bitMap->getRGBToGray(blue, green, red);
                theNewBitMapArray[row * width + (col / bytesPerPixel)] = result;
            }
        }

        //initializing the new header of the bitMap8Bits
        Headers::Header theNewHeader;
        BMPFunctions::init8BitsBMPHeader(theNewHeader, bitMap, theNewPallete, theNewBitMapArray);


        //initializing the new DIBHeader of the bitMap8Bits
        Headers::DIBHeader theNewDIBHeader;
        BMPFunctions::init8BitsBMP_DIBHeader(theNewDIBHeader, bitMap);

        delete bitMap;
        bitMap = new BitMap8Bits(theNewHeader, theNewDIBHeader, theNewPallete, theNewBitMapArray);

    }

}