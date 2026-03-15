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

    for (size_t i = 0; i < 10000; ++i)
    {
        Matrix *a = matrix_create(25, 35, 0);
        if (!a)
            return 1;

        fill_random(a);

        matrix_print(a);

        Matrix *b = matrix_create(35, 42, 0);
        if (!b)
            return 1;

        fill_random(b);

        matrix_print(b);

        Matrix *c = matrix_mulitply(a, b);
        if (!c)
            return 1;

        matrix_print(c);

        matrix_free(a);
        matrix_free(b);
        matrix_free(c);
    }

    return 0;
}