cmake_minimum_required(VERSION 3.16)
set(CMAKE_CUDA_COMPILER "/usr/bin/nvcc")

project(CUDA_MAT_MUL LANGUAGES C CXX CUDA)
message(STATUS  ${PROJECT_NAME})
add_executable( ${PROJECT_NAME}
    main.cu
)
