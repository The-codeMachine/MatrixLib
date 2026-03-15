#include <stdio.h>
#include "../src/include/matrix.h"

int main() {
    Matrix* matrix = matrix_create(25, 25);

    print_matrix(matrix);

    matrix_free(matrix);

    return 0;
}