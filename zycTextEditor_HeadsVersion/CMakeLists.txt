cmake_minimum_required(VERSION 4.3)
project(zycTextEditor)

set(CMAKE_CXX_STANDARD 26)

add_executable(zycTextEditor main.cpp
        zycFastRead.h
        zycTextEditorFunctions.h)
