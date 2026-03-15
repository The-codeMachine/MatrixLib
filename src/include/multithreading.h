#ifndef MULTITHREADING_H
#define MULTITHREADING_H

#include "matrix.h"

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
Matrix* matrix_multiply_mt(Matrix* a, Matrix* b, int threads);

#endif