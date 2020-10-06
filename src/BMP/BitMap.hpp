#pragma once
#include "Headers.hpp"
#include <vector>
namespace BitMap{
class BitMap8Bits;
class BitMap24Bits;

class BitMapAbstract{
protected:
    typedef std::vector<Headers::colorTupple> ColorPalleteType;
    typedef std::vector<uint8_t> IntensityType;

private:
    Headers::Header m_headerInfo;
    Headers::DIBHeader m_DIBHeaderInfo;
    ColorPalleteType m_colorPallete;
    IntensityType m_byteArray;

public:
    /**
     * @brief constructor
     *
     * @param headerInfo the information of the header
     * @param DIBHeaderInfo the information of the DIBheader
    */
    BitMapAbstract(const Headers::Header& headerInfo, const Headers::DIBHeader& DIBHeaderInfo);


    /**
     * @brief constructor
     *
     * @param headerInfo the information of the header
     * @param DIBHeaderInfo the information of the DIBheader
     * @param colorPallete the file's colorPallete
     * @param bitMapArray the bitMapArray of the bmp file
    */
    BitMapAbstract(const Headers::Header& headerInfo, const Headers::DIBHeader& DIBHeaderInfo,
    ColorPalleteType& colorPallete, IntensityType& bitMapArray);

    /**
     * @brief reads the informaton from the bmp file, initializing the
     * header and dibHeader and allocates the new 8/24 bits bit-map
     *
     * @param imageFile the bmp file which we read the information from
    */
    void fromFile(std::ifstream& imageFile);

    /**
     * @brief takes an object of a bmp file and prints his information into
     * a bmp file
     *
     * @param imagePath the path to the new file we want to create
    */
    void toFile(const std::string imagePath);
    /**
     * @brief returns the height of the bitMapArray
     *
     * @return the the height of the bitMapArray
    */
    size_t getHeight() const;

    /**
     * @brief returns the width of the bitMapArray
     *
     * @return the the width of the bitMapArray
    */
    size_t getWidth() const;

    /**
     * @brief returns the collorPallete of the bmp
     *
     * @return the the height collorPallete of the bmp
    */
    ColorPalleteType& getColorPallete();

    /**
     * @brief returns how many bytes does a single pixel take
     *
     * @return thow many bytes does a single pixel take
    */
    size_t getBytesPerPIxel() const;

    /**
     * @brief returns the bitMapArray of the bmp file
     *
     * @return the bitMapArray of the bmp file
    */
    IntensityType& getBitMapArray();

    /**
     * @brief rotates the photo 90 degrees clockwise
     *
    */
    void rotate90Degrees();

    /**
     * @brief rset the bitMapArray height
     *
     * @param height the wanted height
     *
    */
    void setBitMapHeight(const uint32_t height);

    /**
     * @brief rset the bitMapArray width
     *
     * @param width the wanted width
     *
    */
    void setBitMapWidth(const uint32_t width);

    /**
     * @brief takes a rgb(composed from 3 uint8) and returns the gray intensity of ot
     *
     * @param blue wanted width
     *
    */
    uint8_t getRGBToGray(const uint8_t blue, const uint8_t green, const uint8_t red) const;

    /**
     * @brief returns the file's header information
     *
     * @return the file's header information
     *
    */
    const Headers::Header& getHeader() const;

    /**
     * @brief returns the file's DIBheader information
     *
     * @return the file's DIBheader information
     *
    */
    const Headers::DIBHeader& getDIBHeader() const;

    /**
     * @brief returns the file's colorPallete size
     *
     * @return he file's colorPallete size
     *
    */
    size_t getColorPalleteSize() const;

    /**
     * @brief converting a colorful photo to a black and white one
     *
     * @param bitMap the picture we want to transform into a black and white one
     *
    */
    static void convertToGray(BitMap::BitMapAbstract* bitMap);

};



class BitMap8Bits : public BitMapAbstract {
private:
    static const size_t m_ColorPalleteSize = 256;
public:
    BitMap8Bits(Headers::Header& theNewHeader, Headers::DIBHeader& theNewDIBHeader, ColorPalleteType& theNewPallete, IntensityType& theNewBitMapArray);

    BitMap8Bits(const Headers::Header& header, const Headers::DIBHeader& dibHeader);

    static size_t getColorPalleteSize();

    static void convertToGray(BitMap::BitMapAbstract* bitMap);
};



class BitMap24Bits : public BitMapAbstract {
private:
    static const size_t m_ColorPalleteSize = 0;
public:
    BitMap24Bits(const Headers::Header& header, const Headers::DIBHeader& dibHeader);

    static size_t getColorPalleteSize();

    static void convertToGray(BitMap::BitMapAbstract* bitMap);
};
}