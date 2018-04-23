project(zad_1 C)
set(CMAKE_C_STANDARD 11)
add_executable(zad_1 zad_1.c)
target_link_libraries(zad_1 m gsl gslcblas)