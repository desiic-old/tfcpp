#reference:
#https://github.com/FloopCZ/tensorflow_cc

#cmake version
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

#libs
find_package(TensorflowCC REQUIRED)

#include dirs
include_directories(../../libs)
include_directories(../../src)
include_directories(../../src/ann)

#linking
add_executable(prog prog.cpp)
target_link_libraries(prog TensorflowCC::Shared)

#end of file