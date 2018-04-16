project(zad_3 C)
set(CMAKE_C_STANDARD 11)
add_executable(zad_3 zad_3.c)
target_link_libraries(zad_3 m gsl gslcblas)