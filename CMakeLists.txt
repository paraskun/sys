cmake_minimum_required(VERSION 3.11)
project(sys C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

include(CTest)

add_subdirectory(gtest)
enable_testing()

add_subdirectory(cmd)
add_subdirectory(lang)