#include "../src/include/multithreading.h"
#include "../src/include/matrix.h"
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
    // set for random number generator seed
    srand(time(NULL));

    Matrix* a = matrix_create(10000, 10000, 0);
    Matrix* b = matrix_create(10000, 10000, 0);

    fill_random(a);
    fill_random(b);

    Matrix* c = matrix_create(10000, 10000, 0);

    matrix_multiply_gpu(a, b, c);

    matrix_free(a);
    matrix_free(b);
    matrix_free(c);

    return 0;
}