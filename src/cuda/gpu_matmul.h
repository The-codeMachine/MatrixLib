#ifndef GPU_MATMUL_H
#define GPU_MATMUL_H

#ifdef __cplusplus
extern "C" {
    #endif

    void gpu_matrix_multiply(
        const float* A, 
        const float* B, 
        float* C, 
        int A_rows, 
        int A_cols, 
        int B_cols
    );

    #ifdef __cplusplus
}

#endif

#endif