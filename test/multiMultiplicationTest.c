#include "../src/include/multithreading.h"
#include "../src/include/matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANDOM_MIN 1.0
#define RANDOM_MAX 10.0

void fill_random(Matrix *a) {
    for (size_t i = 0; i < a->rows; ++i) {
        for (size_t j = 0; j < a->cols; ++j) {
            double r = (double)rand() / RAND_MAX;
            double value = RANDOM_MIN + r * (RANDOM_MAX - RANDOM_MIN);

            matrix_set(a, i, j, value);
        }
    }
}

int main() {
    // set for random number generator seed
    srand(time(NULL));

    clock_t start, end;

    start = clock();

    Matrix *a = matrix_create(5000, 5000, 0);
    if (!a)
        return 1;

    fill_random(a);   

    Matrix *b = matrix_create(5000, 5000, 0);
    if (!b)
        return 1;

    fill_random(b);

    Matrix *c = matrix_multiply_cpu_mt(a, b, 16);
    if (!c)
        return 1;

    matrix_free(a);
    matrix_free(b);
    matrix_free(c);

    end = clock();

    printf("Execution time: %f seconds\n", ((double) (end - start)) / CLOCKS_PER_SEC);

    return 0;
}