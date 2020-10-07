#include "CommandLineParser.hpp"
#include <string>
#include <sstream>
#include <regex>

namespace commandLineParser {

size_t const argvMatrix = 6;
size_t const argvImage = 5;
size_t const argvHash = 5;
size_t const argvClear = 3;
size_t const argvSearchOneIput = 6;
size_t const argvSearchTwoInput = 7;

Operation::Operations_enum Operation::getOperation (int argc, char** argv) {

    if (argc < 3) {
        return noSuchOperation;
    }
    std::stringstream commandLine;

    int i = 1;
    while ( i < argc) {
        commandLine << argv[i];
        if (i != argc -1) {
            commandLine << ' ';
        }
        i++;
    }
    std::string argvString = commandLine.str();

    std::regex addMatrixTask("matrix add");
    std::regex multMatrixTask("matrix multiply");
    std::regex convertImageToGrayTask("image convert");
    std::regex rotateImageTask("image rotate");
    std::regex crc32Task("hash crc32");
    std::regex clearCacheTask("cache clear");
    std::regex searchTask("cache search");
    std::regex pathToFileRegex("(( )^)+\\.(( )^)+");

    std::smatch matcher;



    if (std::string(argv[1]) == "cache") {
        if (std::string(argv[2]) != "search" && std::string(argv[2]) != "clear") {
            return noSuchOperation;
        }
    }
    std::string operationString = std::string(argv[1]) + " " + std::string(argv[2]);

    //checks which operation we have to do
    if (std::regex_match(operationString, matcher, addMatrixTask) && (argc == argvMatrix)) {
        return Operation::addMatrixOperation;
    } else if (std::regex_match(operationString, matcher, multMatrixTask) && (argc == argvMatrix)) {
        return Operation::multiplyMatrixOperation;
    } else if (std::regex_match(operationString, matcher, rotateImageTask) && (argc == argvImage)) {
        return Operation::rotateImage;
    } else if (std::regex_match(operationString, matcher, convertImageToGrayTask) && (argc == argvImage)) {
        return Operation::convertToGrayScale;
    } else if (std::regex_match(operationString, matcher, crc32Task) && (argc == argvHash)) {
        return Operation::crc32Operation;
    } else if (std::regex_match(operationString, matcher, clearCacheTask) && (argc == argvClear)) {
        return Operation::clearCache;
    } else if (std::regex_match(operationString, matcher, searchTask) &&  ((argc == argvSearchOneIput) || 
    (argc == argvSearchTwoInput))) {

        std::string whatToSearch = std::string(argv[3]) + " " + std::string(argv[4]);

        if ((std::regex_match(whatToSearch, matcher, multMatrixTask) && (argc == argvSearchTwoInput)) ||
        (std::regex_match(whatToSearch, matcher, addMatrixTask) && (argc == argvSearchTwoInput))) {
            return Operation::searchInCacheMatrix;
        }

        if ((std::regex_match(whatToSearch, matcher, multMatrixTask) && (argc == argvSearchOneIput)) ||
        (std::regex_match(whatToSearch, matcher,addMatrixTask) && (argc == argvSearchOneIput))){
            return Operation::noSuchOperation;
        }

        return Operation::searchInCacheOneInput;
    }
    return Operation::noSuchOperation;
}




}