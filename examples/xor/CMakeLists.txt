##!
#\file
#\brief Cmake programme,
#       Requirement: TensorFlow C++
#       https://github.com/FloopCZ/tensorflow_cc
##

#test
foreach(Var First Second Third)
  message("${Var}")
endforeach()

#cmake init
message("\n================================================================================")
message("Base configs:")
message("C++ standard: C++17")
cmake_minimum_required(VERSION 3.10)
add_definitions(-Wfatal-errors)
set(CMAKE_CXX_STANDARD 17)
set(Top "../..")

#find libs
message("\nFinding TensorFlow C++ package...")
find_package(TensorflowCC REQUIRED)

#set include dirs
message("\nSetting include dirs...")
include_directories(${Top}/libs)
include_directories(${Top}/src)

#set source files
message("\nSetting source files...")
aux_source_directory(${Top}/src             Top_Files)
aux_source_directory(${Top}/src/tfcpp       Tfcpp_Files)
aux_source_directory(${Top}/src/tfcpp/ann   Tfcpp_Ann_Files)
aux_source_directory(${Top}/src/tfcpp/miscs Tfcpp_Miscs_Files)
message("${Top_Files}")
message("${Tfcpp_Files}")
message("${Tfcpp_Ann_Files}")
message("${Tfcpp_Miscs_Files}")

#set executable and target
message("\nAdding executable...")
add_executable(prog 
  prog.cpp     
  ${Top_Files}
  ${Tfcpp_Files}
  ${Tfcpp_Ann_Files}
  ${Tfcpp_Miscs_Files}
)

target_link_libraries(prog TensorflowCC::Shared)
message("Config done.")
message("\n================================================================================")

#eof