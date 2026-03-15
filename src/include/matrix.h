#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

/*
For now matrixes will only have an int for their type,
will make it a void** later, for other types as well
*/

typedef struct {
    size_t rows;
    size_t cols;
    double* data; // contiguous memory
} Matrix;

// Creations and destruction

void matrix_free(Matrix* matrix);
Matrix* matrix_create(size_t rows, size_t cols, double initValue);

// Getters / Setters

double matrix_get(Matrix* matrix, size_t row, size_t col);
void matrix_set(Matrix* matrix, size_t row, size_t col, double value);

// Basic Operations

Matrix* matrix_add(Matrix* a, Matrix* b);
Matrix* matrix_subtract(Matrix* a, Matrix* b);

Matrix* matrix_scalar_multiplication(Matrix* a, double scalar);

Matrix* matrix_transpose(Matrix* original);

// Advance operations

Matrix* matrix_mulitply(Matrix* a, Matrix* b);

// debugging functions

void matrix_print(Matrix* matrix);

#endif