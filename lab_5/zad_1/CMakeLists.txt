cmake_minimum_required(VERSION 3.10)
project(zad_1)
set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp perkolacja.cpp perkolacja.h)
add_executable(zad_1 ${SOURCE_FILES})
target_link_libraries(zad_1 m gsl gslcblas)


