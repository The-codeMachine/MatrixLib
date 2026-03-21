#include "../src/include/matrix.h"
#include "../src/include/multithreading.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANDOM_MIN 1.0
#define RANDOM_MAX 10.0

void fill_random(Matrix *a) {
    for (size_t i = 0; i < a->rows; ++i)
    {
        for (size_t j = 0; j < a->cols; ++j)
        {

            double r = (double)rand() / RAND_MAX;
            double value = RANDOM_MIN + r * (RANDOM_MAX - RANDOM_MIN);

            matrix_set(a, i, j, value);
        }
    }
}

int main() {
    srand(time(NULL));

    Matrix* a = matrix_create(3, 5, 0);
    Matrix* b = matrix_create(5, 3, 0);
    Matrix* c = matrix_create(3, 3, 0);

    fill_random(a);
    fill_random(b);

    matrix_print(a);
    matrix_print(b);

    matrix_multiply(a, b, c, BACKEND_CPU, 4);

    matrix_print(c);

    matrix_free(c);
    
    printf("------------------------------------------\n\n");
    
    c = matrix_create(3, 3, 0);
    matrix_multiply(a, b, c, BACKEND_GPU, -1);

    matrix_print(c);

    matrix_free(a);
    matrix_free(b);
    matrix_free(c);

    return 0;
}