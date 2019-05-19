#reference:
#https://github.com/FloopCZ/tensorflow_cc

#cmake version
cmake_minimum_required(VERSION 3.10)
add_definitions(-Wfatal-errors)
set(CMAKE_CXX_STANDARD 17)

#programme info
find_package(TensorflowCC REQUIRED)
add_executable(prog prog.cpp)
target_link_libraries(prog TensorflowCC::Shared)

#end of file