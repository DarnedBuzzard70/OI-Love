cmake_minimum_required(VERSION 4.4)
project(zycHuffmanCompressor)

set(CMAKE_CXX_STANDARD 26)

add_executable(zycHuffmanCompressor main.cpp
        zycPQ.h
        zycPQ.h
        compressor.cpp
        hashtable.cpp
        huffman.cpp
        minheap.cpp)
