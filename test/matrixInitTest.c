#include <stdio.h>
#include "../src/include/matrix.h"

int main() {
    Matrix* matrix = matrix_create(5, 5, 4);

    matrix_print(matrix);

    matrix_set(matrix, 3, 3, -4); // position is 0-4 

    matrix_print(matrix);

    matrix_free(matrix);

    return 0;
}