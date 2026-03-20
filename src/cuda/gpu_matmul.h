#ifndef GPU_MATMUL_H
#define GPU_MATMUL_H

#ifdef __cplusplus
extern "C" {
    #endif

    void gpu_matrix_multiply(
        const double* A,
        const double* B, double* C, int A_rows,
        int A_cols, int B_cols
    );

    #ifdef __cplusplus
}

#endif

#endif