project(zad_4 C)
set(CMAKE_C_STANDARD 11)
add_executable(zad_4 zad_4.c)
target_link_libraries(zad_4 m gsl gslcblas)