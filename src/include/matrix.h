#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

typedef struct {
    int rows;
    int cols;
    void** data;
} Matrix;

// Creations and destruction

void matrix_free(Matrix* matrix);
Matrix* matrix_create(size_t rows, size_t cols);

Matrix matrix_mulitply(Matrix* a, Matrix* b);
Matrix matrix_divide(Matrix* a, Matrix* b);

// Basic Operations

Matrix* matrix_add(Matrix* a, Matrix* b);
Matrix* matrix_subtract(Matrix* a, Matrix* b);

Matrix* matrix_scalar_multiplication(Matrix* a, int scalar);

// debugging functions
void print_matrix(Matrix* matrix);

#endif