#include "BMP/bmp_tester.hpp"
#include "matrix/MatrixParser.hpp"
#include "matrix/MatrixOperation.hpp"
#include "matrix/MatrixExceptions.hpp"
#include "CommandLineParser.hpp"
#include "BMP/BMPOperation.hpp"
#include "BMP/Exceptions.hpp"
#include "crc/crcOperation.hpp"
#include "CacheManager.hpp"
#include "CacheSearcher.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <sys/stat.h>

int main(int argc, char** argv) {
    size_t const startPositionInputFiles = 3;

    std::filesystem::path program =  argv[0];

    std::filesystem::path workdir = program.remove_filename();

    workdir /= "cache";

    mkdir(workdir.c_str(), 0777);

    cacheManager::CacheManager manager(workdir);

    manager.rebuildLRU();

    commandLineParser::Operation::Operations_enum task = commandLineParser::Operation::getOperation(argc, argv);
    try {
    // checks what operation we should do
    switch (task) {
        case commandLineParser::Operation::addMatrixOperation:
             MatrixOperation::matOperation(argv[startPositionInputFiles],
            argv[startPositionInputFiles + 1], argv[startPositionInputFiles + 2], manager,  MatrixOperation::add); 
            break;
        case commandLineParser::Operation::multiplyMatrixOperation:
            MatrixOperation::matOperation(argv[startPositionInputFiles],
            argv[startPositionInputFiles + 1], argv[startPositionInputFiles + 2], manager,  MatrixOperation::multiply); 
            break;
        case commandLineParser::Operation::rotateImage:
            BMPOperation::bmpOperation(argv[startPositionInputFiles],
             argv[startPositionInputFiles + 1], manager, BMPOperation::rotateImage);
            break;
        case commandLineParser::Operation::convertToGrayScale:
            BMPOperation::bmpOperation(argv[startPositionInputFiles],
             argv[startPositionInputFiles + 1], manager, BMPOperation::convertToGrayScale);
            break;
        case commandLineParser::Operation::crc32Operation:
        {
            std::string inputFile(argv[startPositionInputFiles]);
            std::string outputFile(argv[startPositionInputFiles + 1]);
            CRCoperation::crcOperationManage(inputFile, outputFile, manager);
            break;
        }
        case commandLineParser::Operation::clearCache:
        {
            manager.clearCache();
            break;
        }

        case commandLineParser::Operation::searchInCacheOneInput:
        {
           CacheSearcher::serarchInCacheOneInput(argv,manager);
            break;
        }
        case commandLineParser::Operation::searchInCacheMatrix:
        {
            CacheSearcher::searchInCacheMatrix(argv, manager);
            break;
        }
        default:
            std::cerr << "no such task";
    }

    } catch (FileExceptions::FileExceptions &e) {
        e.printException();
    } catch (cacheManager::CantFindSavedTimeException e) {
        e.print();
    } catch (Exceptions::ErrorNullMatrix e) {
       e.printException();
    } catch (Exceptions::ErrorMatrixSizeNotAppopriate e) {
       e.printException();
    } catch (Exceptions::ErrorExceedMatrix e) {
       e.printException();
    } catch (Exceptions::ErrorCantMult e) {
       e.printException();
    } catch (Exceptions::ErrorCantAllocateMatrix e) {
       e.printException();
    } catch (Exceptions::ErrorCantAdd e) {
       e.printException();
    } catch (...) {
        std::cerr << "unexpected error occurd";
    }




}
