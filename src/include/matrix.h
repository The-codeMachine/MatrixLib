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
    float* data; // contiguous memory
} Matrix;

// Creations and destruction

void matrix_free(Matrix* matrix);
Matrix* matrix_create(size_t rows, size_t cols, float initValue);

// Getters / Setters

float matrix_get(Matrix* matrix, size_t row, size_t col);
void matrix_set(Matrix* matrix, size_t row, size_t col, float value);

// Basic Operations

Matrix* matrix_add(Matrix* a, Matrix* b);
Matrix* matrix_subtract(Matrix* a, Matrix* b);

Matrix* matrix_scalar_multiplication(Matrix* a, float scalar);

Matrix* matrix_transpose(Matrix* original);

// debugging functions

void matrix_print(Matrix* matrix);

#endif