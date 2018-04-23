project(zad_5 C)
set(CMAKE_C_STANDARD 11)
add_executable(zad_5 zad_5.c)
target_link_libraries(zad_5 m gsl gslcblas)