#include "../src/include/matrix.h"
#include <stdio.h>

int main() {
    Matrix* a = matrix_create(2, 4, 5);

    matrix_print(a);
    matrix_set(a, 1, 0, -4);
    matrix_print(a);

    Matrix* transpose = matrix_transpose(a);

    matrix_print(transpose);

    matrix_free(a);
    matrix_free(transpose);

    return 0;
}