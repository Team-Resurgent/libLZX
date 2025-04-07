cmake_minimum_required(VERSION 3.25)
project(LZX)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "lib")
endif()

include_directories(lzx)

add_library(LZX SHARED main.cpp lzx/lzx_decoder.c lzx/lzx_encoder.c)
