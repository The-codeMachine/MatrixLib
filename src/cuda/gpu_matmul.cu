#include <cuda_runtime.h>
#include "gpu_matmul.h"

__global__
void matmul_kernel(double* A, double* B, double* C, int A_rows, int A_cols, int B_cols) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < A_rows && col < B_cols) {
        double sum = 0.0;

        for (int k = 0; k < A_cols; ++k) {
            sum += A[row * A_cols + k] * B[k * B_cols + col];
        }

        C[row * B_cols + col] = sum;
    }
}

extern "C" 
void gpu_matrix_multiply(const double* A, const double* B, double* C,
int A_rows, int A_cols, int B_cols) {
    double *d_A, *d_B, *d_C;

    size_t size_A = A_rows * A_cols * sizeof(double);
    size_t size_B = A_cols * B_cols * sizeof(double);
    size_t size_C = A_rows * B_cols * sizeof(double);

    cudaMalloc(&d_A, size_A);
    cudaMalloc(&d_B, size_B);
    cudaMalloc(&d_C, size_C);

    cudaMemcpy(d_A, A, size_A, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size_B, cudaMemcpyHostToDevice);

    dim3 blockSize(16, 16);
    dim3 gridSize((B_cols + 15) / 16, (A_rows + 15) / 16);

    matmul_kernel<<<gridSize, blockSize>>>(d_A, d_B, d_C,
    A_rows, A_cols, B_cols);

    cudaMemcpy(C, d_C, size_C, cudaMemcpyDeviceToHost);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
}
