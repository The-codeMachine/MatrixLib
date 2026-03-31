
#include "../src/include/matrix.h"
#include "../src/include/matrixMultiply.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANDOM_MIN 1.0f
#define RANDOM_MAX 10.0f

void fill_random(Matrix *a) {
    for (int i = 0; i < a->rows; ++i)
    {
        for (int j = 0; j < a->cols; ++j)
        {

            float r = (float)rand() / RAND_MAX;
            float value = RANDOM_MIN + r * (RANDOM_MAX - RANDOM_MIN);

            matrix_set(a, i, j, value);
        }
    }
}

int main() {
    srand(time(NULL));
    
    Matrix* a = matrix_create(2000, 2000, 0);
    Matrix* b = matrix_create(2000, 2000, 0);
    Matrix* c = matrix_create(2000, 2000, 0);
    
    fill_random(a);
    fill_random(b);

    clock_t begin = clock();
    
    matrix_multiply(a, b, c, BACKEND_CPU, 8);

    matrix_free(a);
    matrix_free(b);
    matrix_free(c);
    
    clock_t end = clock();

    printf("Time spent: %f seconds\n", ((double)(end - begin)) / CLOCKS_PER_SEC);

    return 0;
}