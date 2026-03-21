#ifndef MULTITHREADING_H
#define MULTITHREADING_H

#include <stddef.h>
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

// Platform independent worker signature
typedef void* (*thread_func)(void*);

int matrix_multiply(Matrix* a, Matrix* b, Matrix* c, Backend backend, int threads);

#endif