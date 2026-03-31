cmake_minimum_required(VERSION 3.20)
project(MatrixLib LANGUAGES C CUDA)

add_library(MatrixLib 
    src/matrix.c
    src/matrixMultiply.c
    src/cuda/gpu_matmul.cu
)

target_include_directories(MatrixLib PUBLIC src/include)

add_executable(test_app test/stresstest.c)

target_link_libraries(test_app MatrixLib)