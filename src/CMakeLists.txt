cmake_minimum_required(VERSION 3.0.0)
project(ex3.out VERSION 0.1.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
add_compile_options(-Wall -Wextra -pedantic -Werror)
enable_testing()

add_executable(ex3.out 
matrix/MatrixExceptions.cpp 
matrix/Matrix.c 
matrix/ErrorCode.c 
matrix/ClassMatrix.cpp 
matrix/MatrixParser.cpp 
matrix/MatrixOperation.cpp 
BMP/BMPOperation.cpp 
BMP/BitMap.cpp 
BMP/bmp_tester.cpp 
BMP/BitMapFactory.cpp 
BMP/BitMapHelpFunctions.cpp 
BMP/Headers.cpp 
BMP/Exceptions.cpp 
crc/crcOperation.cpp 
crc/crc32c.c 
CacheSearcher.cpp
CommandLineParser.cpp
CacheList.cpp 
FileNode.cpp
CacheManager.cpp
main.cpp)

#target_link_libraries(ex3 Matrix MatrixParser bmp_tester BitMapFactory BitMap Headers Exceptions BMPFunctions MatrixParser ClassMatrix MatrixExceptions  ErrorCode MatrixOperation)
#
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)