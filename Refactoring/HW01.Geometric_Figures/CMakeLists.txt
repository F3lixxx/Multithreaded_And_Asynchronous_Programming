cmake_minimum_required(VERSION 3.26)

project(refac)

set(CMAKE_CXX_STANDARD 17)

add_executable(refac main.cpp shape.cpp shape.h transform.cpp transform.h)