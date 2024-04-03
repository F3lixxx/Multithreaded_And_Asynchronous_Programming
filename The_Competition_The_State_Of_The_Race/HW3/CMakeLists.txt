cmake_minimum_required(VERSION 3.20)

project(HW3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Data main.cpp   "line.cpp" "rectangle.cpp" "parallelepiped.cpp" "circle.cpp" "cylinder.cpp" "line.h" "cylinder.h" "parallelepiped.h" "rectangle.h" "shape.h" "circle.h")