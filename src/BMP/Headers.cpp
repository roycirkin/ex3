#include "Headers.hpp"
#include "Exceptions.hpp"

namespace Headers{

//reading the header and checking that he is valid 
void Header::fromfStream(std::ifstream& imageFile){
    if (!imageFile) {
       throw FileExceptions::OpenFileExceptionForReading();
    }
    imageFile.read((char *) this,sizeof(Header));

    if (signature != BMPmagic) {
        throw FileExceptions::WrongBMPFileException();
    }
    size_t pos = imageFile.tellg();
    imageFile.seekg(0, std::ios::end);
    size_t end = imageFile.tellg();
    imageFile.seekg(pos, std::ios::beg);
    if (sizeOfFile != end) {
           throw FileExceptions::WrongBMPFileException();
    }
}

//reading the DIBheader and checking that he is valid 
void DIBHeader::fromfStream(std::ifstream& imageFile){
    if (!imageFile) {
        throw FileExceptions::OpenFileExceptionForReading();    
    }
    imageFile.read((char *) this, sizeof(DIBHeader));

    if(this->sizeOfHeader != sizeof(*this)) {
        throw FileExceptions::WrongBMPFileException();        
    }
    if (this->colorsInColorPallete != 0 && this->bitesPerPixel != 8) {
        throw FileExceptions::WrongBMPFileException();
    }
}











}