#include <cuda_runtime.h>
#include "gpu_matmul.h"

#define TILE_SIZE 16

__global__
void matmul_kernel(const float* __restrict__ A, const float* __restrict__ B, float* __restrict__ C, 
    int A_rows, int A_cols, int B_cols) {
    __shared__ float As[TILE_SIZE][TILE_SIZE];
    __shared__ float Bs[TILE_SIZE][TILE_SIZE];

    int row = blockIdx.y * TILE_SIZE + threadIdx.y;
    int col = blockIdx.x * TILE_SIZE + threadIdx.x;

    float sum = 0.0f;

    int tiles = (A_cols + TILE_SIZE - 1) / TILE_SIZE;

    for (int t = 0; t < tiles; ++t) {

        int A_col = t * TILE_SIZE + threadIdx.x;
        int B_row = t * TILE_SIZE + threadIdx.y;

        if (row < A_rows && A_col < A_cols)
            As[threadIdx.y][threadIdx.x] = A[row * A_cols + A_col];
        else
            As[threadIdx.y][threadIdx.x] = 0.0f;

        if (B_row < A_cols && col < B_cols)
            Bs[threadIdx.y][threadIdx.x] = B[B_row * B_cols + col];
        else
            Bs[threadIdx.y][threadIdx.x] = 0.0f;

        __syncthreads();

        for (int k = 0; k < TILE_SIZE; ++k)
            sum += As[threadIdx.y][k] * Bs[k][threadIdx.x];

        __syncthreads();
    }

    if (row < A_rows && col < B_cols)
        C[row * B_cols + col] = sum;
}

extern "C"
#include <stdio.h>
void gpu_matrix_multiply(const float* A, const float* B, float* C, 
    int A_rows, int A_cols, int B_cols) {
    float *d_A, *d_B, *d_C;

    size_t size_A = A_rows * A_cols * sizeof(float);
    size_t size_B = A_cols * B_cols * sizeof(float);
    size_t size_C = A_rows * B_cols * sizeof(float);

    cudaError_t m_err = cudaMalloc(&d_A, size_A);
    if (m_err != cudaSuccess) {
        printf("CUDA error: %s\n", cudaGetErrorString(m_err));
    }

    m_err = cudaMalloc(&d_B, size_B);
    if (m_err != cudaSuccess) {
        printf("CUDA error: %s\n", cudaGetErrorString(m_err));
    }

    m_err = cudaMalloc(&d_C, size_C);
    if (m_err != cudaSuccess) {
        printf("CUDA error: %s\n", cudaGetErrorString(m_err));
    }

    m_err = cudaMemcpy(d_A, A, size_A, cudaMemcpyHostToDevice);
    if (m_err != cudaSuccess) {
        printf("CUDA error: %s\n", cudaGetErrorString(m_err));
    }

    m_err = cudaMemcpy(d_B, B, size_B, cudaMemcpyHostToDevice);
    if (m_err != cudaSuccess) {
        printf("CUDA error: %s\n", cudaGetErrorString(m_err));
    }

    dim3 blockSize(TILE_SIZE, TILE_SIZE);
    dim3 gridSize(
        (B_cols + TILE_SIZE - 1) / TILE_SIZE,
        (A_rows + TILE_SIZE - 1) / TILE_SIZE);

    matmul_kernel<<<gridSize, blockSize>>>(
        d_A, d_B, d_C,
        A_rows, A_cols, B_cols);

    cudaDeviceSynchronize();
    cudaError_t err = cudaGetLastError();

    if (err != cudaSuccess) 
        printf("Kernel launch error: %s\n", cudaGetErrorString(err));

    cudaMemcpy(C, d_C, size_C, cudaMemcpyDeviceToHost);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
}
