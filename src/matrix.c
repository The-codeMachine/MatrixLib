#include "include/matrix.h"

#include <stdio.h>
#include <stdlib.h>

// ---- Creation and Destruction Functions ----

// Frees the matrix pointer, call to prevent a memory leak
void matrix_free(Matrix* matrix) {
    if (matrix == NULL)
        return;

    // free the internal array first
    if (matrix->data != NULL) 
        free(matrix->data);

    free(matrix);
}

// Initializes a matrix with a set number of rows, and columns, each will have a random value 
Matrix* matrix_create(size_t rows, size_t cols) {
    // Allocate memory for the struct itself
    Matrix* matrix = malloc(sizeof(Matrix));

    if (matrix == NULL)
        return NULL;

    matrix->rows = rows;
    matrix->cols = cols;

    // Allocate memory for the internal array
    matrix->data = malloc(rows * sizeof(int*));

    for (int i = 0; i < rows; ++i) {
        matrix->data[i] = malloc(cols * sizeof(int));
    }

    if (matrix->data == NULL) {
        matrix_free(matrix); // no memory leak
        return NULL;
    }

    return matrix;
}

// ---- Basic operations ----

// Adds two matrices together (both matrices must have the same number of columns, and rows)
Matrix* matrix_add(Matrix* a, Matrix* b) {
    if (a->rows != b->rows || a->cols != b->cols)
        return NULL; // cannot multiply

    Matrix* c = matrix_create(a->rows, a->cols);

    for (int i = 0; i < a->rows; ++i) {
        for (int j = 0; j < a->cols; ++j) {
            c->data[i * c->cols + j] = (a->data[i * a->cols + j] + b->data[i * b->cols + j]);
        }
    }

    return c;
}

// Subtracts two matrices from each other (both matrices must have the same columns, and rows)
Matrix* matrix_subtract(Matrix* a, Matrix* b) {
    if (a->rows != b->rows || a->cols != b->cols)
        return NULL;

    Matrix* c = matrix_create(a->rows, a->cols);

    for (int i = 0; i < a->rows; ++i) {
        for (int j = 0; j < a->cols; ++j) {
            c->data[i * c->cols + j] = (a->data[i * a->cols + j] - b->data[i * b->cols + j]);
        }
    }

    return c;
}

// Multiplies a matrix by a scalar
Matrix* matrix_scalar_multiplication(Matrix* a, int scalar) {
    Matrix* out = matrix_create(a->rows, a->cols);

    for (int i = 0; i < out->rows; ++i) {
        for (int j = 0; j < out->cols; ++j) {
            out->data[i * out->cols + j] = (a->data[i * a->cols + j] * scalar);
        }
    }

    return out;
}

/*
Accessing the element m[i][j]:
    m->data[i * m->cols + j] = 10;
*/

// debugging functions
void print_matrix(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; ++i) {
        printf("[");
        
        for (int j = 0; j < matrix->cols; ++j) {
            printf("%d, ", matrix->data[i * matrix->cols + j]);
        }

        printf("],\n");
    }
}