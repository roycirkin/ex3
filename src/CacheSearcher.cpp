#include "CacheSearcher.hpp"
#include <sstream>
#include "matrix/MatrixParser.hpp"


namespace CacheSearcher {

    void serarchInCacheOneInput(char** argv, cacheManager::CacheManager& manager) {

            //searching in the cache
            std::stringstream ss;
            ss << argv[3] << "_" << argv[4];
            std::ifstream inputFile(std::string(argv[5]), std::ios::in);
            char c;
            while (inputFile.get(c)) {
                ss << c;
            }

            std::string searchInCache(ss.str());
            std::string val;
            if (manager.searchKey(searchInCache, val)) {
                std::chrono::time_point time = manager.getSavedTime(searchInCache);
                std::time_t time_c = std::chrono::system_clock::to_time_t(time);
                std::tm time_tm = *std::localtime(&time_c);
                std::cout << "result found in cache saved on: " << " day: " << time_tm.tm_mday << " hour: " << time_tm.tm_hour 
                << " minute: " << time_tm.tm_min;
            } else {
                std::cout << "no match found";
            }
            inputFile.close();
    }


    void searchInCacheMatrix(char** argv, cacheManager::CacheManager& manager) {

        //searching in the cache
        std::stringstream ss;
        ss << argv[3] << "_" << argv[4];
        std::ifstream inputFile1(std::string(argv[5]), std::ios::in);
        std::ifstream inputFile2(std::string(argv[6]), std::ios::in);

        matrix::Matrix m1 = MatrixParsering::getMatrixFromFile(argv[5]);
        matrix::Matrix m2 = MatrixParsering::getMatrixFromFile(argv[6]);
        ss << m1 << m2;

        std::string searchInCache(ss.str());
        std::string val;

        if (manager.searchKey(searchInCache, val)) {
            std::chrono::time_point time = manager.getSavedTime(searchInCache);
            std::time_t time_c = std::chrono::system_clock::to_time_t(time);
            std::tm time_tm = *std::localtime(&time_c);
            std::cout << "result found in cache saved on" << " day: " << time_tm.tm_mday << " hour: " << time_tm.tm_hour 
            << " minute: " << time_tm.tm_min;
        } else {
            std::cout << "no match found";
        }
        inputFile1.close();
        inputFile2.close();


    }





}