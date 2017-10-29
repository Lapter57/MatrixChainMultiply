cmake_minimum_required(VERSION 3.8)
project(MultMatrix)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Matrix.h MatrixDef.h main2.cpp)
add_executable(MultMatrix ${SOURCE_FILES})