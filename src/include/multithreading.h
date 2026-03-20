#ifndef MULTITHREADING_H
#define MULTITHREADING_H

#include "matrix.h"
#include "../cuda/gpu_matmul.h"

typedef enum {
    BACKEND_CPU,
    BACKEND_GPU
} Backend;

typedef struct {
    Matrix* a;
    Matrix* b;
    Matrix* c;
    size_t row_start;
    size_t row_end;
} ThreadData;

// Worker function
void* matrix_worker(void* arg);

// Thread creation
Matrix* matrix_multiply_cpu_mt(Matrix* a, Matrix* b, int threads);

// GPU multithreading
void matrix_multiply_gpu(Matrix* a, Matrix* b, Matrix* c) {
    gpu_matrix_multiply(a->data, b->data, c->data, a->rows, a->cols, b->cols);
}

// TODO: migrate all of the multithreading fucntions into one simple matrix_multiply function
// that determines what to use (GPU/CPU) based off the calculations, how many threads, etc. 

void matrix_multiply_mt(Matrix* a, Matrix* b, Matrix* c, Backend backend) {
    if (backend == BACKEND_GPU) {
        matrix_multiply_gpu(a, b, c);
    } else {
        c = matrix_multiply_cpu_mt(a, b, 4); 
    }
}

#endif