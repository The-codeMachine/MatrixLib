#include "include/multithreading.h"
#include <stdlib.h>

DWORD WINAPI matrix_worker(LPVOID arg) {
    ThreadData* data = (ThreadData*)arg;

    Matrix* a = data->a;
    Matrix* b_t = data->b; // already transposed
    Matrix* c = data->c;

    for (size_t i = data->row_start; i < data->row_end; ++i) {
        for (size_t j = 0; j < b_t->rows; ++j) {

            double dotProduct = 0.0;

            for (size_t k = 0; k < a->cols; ++k) {
                dotProduct += a->data[i * a->cols + k] *
                              b_t->data[j * b_t->cols + k];
            }

            c->data[i * c->cols + j] = dotProduct;
        }
    }

    return 0;
}

Matrix* matrix_multiply_cpu_mt(Matrix* a, Matrix* b, int threads) {

    if (!a || !b || threads <= 0)
        return NULL;

    if (a->cols != b->rows)
        return NULL;

    Matrix* c = matrix_create(a->rows, b->cols, 0);
    Matrix* b_t = matrix_transpose(b);

    HANDLE* thread_pool = malloc(sizeof(HANDLE) * threads);
    ThreadData* thread_data = malloc(sizeof(ThreadData) * threads);

    size_t rows_per_thread = a->rows / threads;

    for (int t = 0; t < threads; ++t) {

        thread_data[t].a = a;
        thread_data[t].b = b_t;
        thread_data[t].c = c;

        thread_data[t].row_start = t * rows_per_thread;

        thread_data[t].row_end = (t == threads - 1)
            ? a->rows
            : (t + 1) * rows_per_thread;

        thread_pool[t] = CreateThread(
            NULL,
            0,
            matrix_worker,
            &thread_data[t],
            0,
            NULL
        );
    }

    for (int t = 0; t < threads; ++t) {
        WaitForSingleObject(thread_pool[t], INFINITE);
        CloseHandle(thread_pool[t]);
    }

    matrix_free(b_t);
    free(thread_pool);
    free(thread_data);

    return c;
}

void matrix_multiply_gpu(Matrix* a, Matrix* b, Matrix* c) {
    gpu_matrix_multiply(a->data, b->data, c->data, a->rows, a->cols, b->cols);
}

void matrix_multiply_mt(Matrix* a, Matrix* b, Matrix* c, Backend backend) {
    if (backend == BACKEND_GPU) {
        matrix_multiply_gpu(a, b, c);
    } else {
        c = matrix_multiply_cpu_mt(a, b, 4); 
    }
}