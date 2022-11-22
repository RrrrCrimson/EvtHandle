cmake_minimum_required(VERSION 3.23)
project(EvtHandle)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)
add_subdirectory(src)
add_executable(EvtHandle main.cpp)
