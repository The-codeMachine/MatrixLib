cmake_minimum_required(VERSION 3.20)
project(MatrixLib LANGUAGES C CUDA)

add_library(MatrixLib 
    src/matrix.c
    src/matrixMultiply.c
    src/cuda/gpu_matmul.cu
)

target_include_directories(MatrixLib PUBLIC src/include)

add_executable(GPU_Stress_Test test/stresstest.c)
add_executable(CPU_Stress_Test test/cpuStressTest.c)

target_link_libraries(GPU_Stress_Test MatrixLib)
target_link_libraries(CPU_Stress_Test MatrixLib)