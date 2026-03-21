#include "include/matrix.h"

#include <stdio.h>
#include <stdlib.h>

// ---- Creation and Destruction Functions ----

// Frees the matrix pointer, call to prevent a memory leak
void matrix_free(Matrix* matrix) {
    if (!matrix)
        return;

    free(matrix->data);
    free(matrix);
}

// Initializes a matrix with a set number of rows, and columns, each will have a random value 
Matrix* matrix_create(size_t rows, size_t cols, double initValue) {
    if (rows == 0 || cols == 0) 
        return NULL;

    // prevent overflow in multiplication
    if (rows > SIZE_MAX / cols)
        return NULL;

    const size_t count = rows * cols;

    // allocate memory for the struct itself
    Matrix* matrix = malloc(sizeof(Matrix));
    if (!matrix)
        return NULL;

    matrix->rows = rows;
    matrix->cols = cols;

    // allocate memory for the internal array
    matrix->data = calloc(count, sizeof(double));
    if (!matrix->data) {
        free(matrix); // no memory leak
        return NULL;
    }

    // init values
    for (size_t i = 0; i < count; ++i) {
        matrix->data[i] = initValue;
    }

    return matrix;
}

// ---- Getters / Setters ----

double matrix_get(Matrix* matrix, size_t row, size_t col) {
    return matrix->data[row * matrix->cols + col];
}

void matrix_set(Matrix* matrix, size_t row, size_t col, double value) {
    matrix->data[row * matrix->cols + col] = value;
}

// ---- Basic operations ----

// Adds two matrices together (both matrices must have the same number of columns, and rows)
Matrix* matrix_add(Matrix* a, Matrix* b) {
    if (a->rows != b->rows || a->cols != b->cols)
        return NULL; // cannot multiply

    Matrix* c = matrix_create(a->rows, a->cols, 0);
    if (!c)
        return NULL;

    for (size_t i = 0; i < a->rows; ++i) {
        for (size_t j = 0; j < a->cols; ++j) {
            matrix_set(c, i, j, (matrix_get(a, i, j) + matrix_get(b, i, j)));
        }
    }

    return c;
}

// Subtracts two matrices from each other (both matrices must have the same columns, and rows)
Matrix* matrix_subtract(Matrix* a, Matrix* b) {
    if (a->rows != b->rows || a->cols != b->cols)
        return NULL;

    Matrix* c = matrix_create(a->rows, a->cols, 0);
    if (!c) 
        return NULL;

    for (size_t i = 0; i < a->rows; ++i) {
        for (size_t j = 0; j < a->cols; ++j) {
            matrix_set(c, i, j, (matrix_get(a, i, j) - matrix_get(b, i, j)));
        }
    }

    return c;
}

// Multiplies a matrix by a scalar
Matrix* matrix_scalar_multiplication(Matrix* a, double scalar) {
    Matrix* out = matrix_create(a->rows, a->cols, 0);
    if (!out)
        return NULL;

    for (size_t i = 0; i < out->rows; ++i) {
        for (size_t j = 0; j < out->cols; ++j) {
            matrix_set(out, i, j, (matrix_get(a, i, j) * scalar));
        }
    }

    return out;
}

// Flips the rows and columns of a matrix
Matrix* matrix_transpose(Matrix* original) {
    Matrix* out = matrix_create(original->cols, original->rows, 0);
    if (!out)
        return NULL;

    for (size_t i = 0; i < original->rows; ++i) {
        for (size_t j = 0; j < original->cols; ++j) {
            matrix_set(out, j, i, matrix_get(original, i, j));
        }
    }

    return out;
}

/*
Accessing the element m[i][j]:
    m->data[i * m->cols + j]
*/

// debugging functions

void matrix_print(Matrix* matrix) {
    for (size_t i = 0; i < matrix->rows; ++i) {
        printf("[");
        
        printf("%8.8f", matrix_get(matrix, i, 0));

        for (size_t j = 1; j < matrix->cols; ++j) {
            printf(", %8.8f", matrix_get(matrix, i, j));
        }

        printf("],\n");
    }
}