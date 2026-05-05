cmake_minimum_required(VERSION 3.31)
project(Simple_RSA)

set(CMAKE_CXX_STANDARD 20)

set(INC_DIR src)

include_directories(${INC_DIR})

add_executable(Simple_RSA main.cpp
        src/RSA.cpp
        src/RSA.h)
