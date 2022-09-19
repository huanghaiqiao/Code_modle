cmake_minimum_required (VERSION 3.4)

project(SOR_openMP)
set(CMAKE_CXX_STANDARD 11)
add_executable(test2 test2.cpp)
 
# openMP settings
FIND_PACKAGE(OpenMP REQUIRED)
if (OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()
