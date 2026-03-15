#include "../src/include/matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANDOM_MIN 0
#define RANDOM_MAX 15

void fill_random(Matrix* a) {
    for (size_t i = 0; i < a->rows; ++i) {
        for (size_t j = 0; j < a->cols; ++j) {
            matrix_set(a, i, j, ((rand() % (RANDOM_MAX - RANDOM_MIN + 1)) + RANDOM_MIN));
        }
    }
}

int main() {
    // set for random number generator seed
    srand(time(NULL));

    Matrix* a = matrix_create(5, 3, 5);
    if (!a)
        return 1;

    fill_random(a);

    matrix_print(a);

    Matrix* b = matrix_create(3, 4, 3);
    if (!b)
        return 1;

    fill_random(b);

    matrix_print(b);

    Matrix* c = matrix_mulitply(a, b);
    if (!c)
        return 1;

    matrix_print(c);

    matrix_free(a);
    matrix_free(b);
    matrix_free(c);

    return 0;
}