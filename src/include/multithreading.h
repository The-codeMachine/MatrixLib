#ifndef MULTITHREADING_H
#define MULTITHREADING_H

#include <windows.h>
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
DWORD WINAPI matrix_worker(LPVOID arg);

// Thread creation
Matrix* matrix_multiply_cpu_mt(Matrix* a, Matrix* b, int threads);

// GPU multithreading
void matrix_multiply_gpu(Matrix* a, Matrix* b, Matrix* c);

// TODO: migrate all of the multithreading fucntions into one simple matrix_multiply function
// that determines what to use (GPU/CPU) based off the calculations, how many threads, etc. 

void matrix_multiply_mt(Matrix* a, Matrix* b, Matrix* c, Backend backend);

#endif