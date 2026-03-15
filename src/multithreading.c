#include "include/multithreading.h"
#include <stdlib.h>
#include <pthread.h>

void* matrix_worker(void* arg) {
    ThreadData* data = (ThreadData*)arg;

    Matrix* a = data->a;
    Matrix* b = data->b;
    Matrix* c = data->c;

    // matrix multplication implementation O(N^3)
    for (size_t i = data->row_start; i < data->row_end; ++i) {
        for (size_t j = 0; j < b->cols; ++j) {
            double dotProduct = 0.0;

            for (size_t k = 0; k < a->cols; ++k) {
                // do not call matrix_get, function calls inside inner loops = less performance
                dotProduct += a->data[i * a->cols + k] * b->data[j * b->cols + k]; 
            }

            c->data[i * c->cols + j] = dotProduct;
        }
    }

    return NULL;
}

Matrix* matrix_multiply_mt(Matrix* a, Matrix* b, int threads) {

    if (!a || !b || threads <= 0)
        return NULL;

    if (a->cols != b->rows)
        return NULL;

    Matrix* c = matrix_create(a->rows, b->cols, 0);
    Matrix* b_t = matrix_transpose(b);

    pthread_t* thread_pool = malloc(sizeof(pthread_t) * threads);
    ThreadData* thread_data = malloc(sizeof(ThreadData) * threads);

    size_t rows_per_thread = a->rows / threads;

    for (int t = 0; t < threads; ++t) {

        thread_data[t].a = a;
        thread_data[t].b = b_t;
        thread_data[t].c = c;

        thread_data[t].row_start = t * rows_per_thread;

        if (t == threads - 1)
            thread_data[t].row_end = a->rows;
        else
            thread_data[t].row_end = (t + 1) * rows_per_thread;

        pthread_create(&thread_pool[t], NULL, matrix_worker, &thread_data[t]);
    }

    for (int t = 0; t < threads; ++t)
        pthread_join(thread_pool[t], NULL);

    matrix_free(b_t);

    free(thread_pool);
    free(thread_data);

    return c;
}