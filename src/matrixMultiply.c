#include "include/matrixMultiply.h"
#include <stdlib.h>

const size_t BLOCK_SIZE = 32; // block size (maybe 64, idk)

#if defined(_WIN32) || defined(_WIN64)
    #define PLATFORM_WINDOWS
    #include <windows.h>
#else
    #define PLATFORM_POSIX
    #include <pthread.h>
#endif

void* matrix_worker(void* arg) {
    ThreadData* data = (ThreadData*)arg;

    Matrix* a = data->a;
    Matrix* b_t = data->b; // already transposed
    Matrix* c = data->c;

    for (size_t ii = 0; ii < a->rows; ii += BLOCK_SIZE) {
        for (size_t jj = 0; jj < b->cols; jj += BLOCK_SIZE) {
            for (size_t kk = 0; kk < a->cols; kk += BLOCK_SIZE) {

                for (size_t i = ii; i < ii + BLOCK_SIZE && i < a->rows; ++i) {
                    for (size_t j = jj; j < jj + BLOCK_SIZE && k < b->cols; ++j) {
                        float sum = c->data[i * c->cols + j];

                        for (size_t k = kk; k < kk + BLOCK_SIZE && k < a->cols; ++k) {
                            sum += a->data[i * a->cols + k] * b->data[k * b->cols + j];
                        }

                        c->data[i * c->cols + j] = sum;
                    }
                }
            }
        }
    }

    return NULL;
}

#ifdef PLATFORM_WINDOWS

typedef struct {
    thread_func func;
    void* arg;
} ThreadStart;

DWORD WINAPI thread_adapter(LPVOID arg) {
    ThreadStart* data = (ThreadStart*)arg;
    data->func(data->arg);
    free(data);

    return 0;
}

#endif

int matrix_multiply_cpu_mt(Matrix* a, Matrix* b, Matrix* c, int threads) {

    if (!a || !b || !c || threads <= 0)
        return -1;

    if (a->cols != b->rows)
        return -1;

    Matrix* b_t = matrix_transpose(b);

    size_t rows_per_thread = a->rows / threads;

#ifdef PLATFORM_WINDOWS

    HANDLE* handles = malloc(sizeof(HANDLE) * threads);
    ThreadData* data = malloc(sizeof(ThreadData) * threads);

    for (int t = 0; t < threads; ++t) {

        data[t] = (ThreadData){
            .a = a,
            .b = b_t,
            .c = c,
            .row_start = t * rows_per_thread,
            .row_end = (t == threads - 1) ? a->rows : (t + 1) * rows_per_thread
        };

        ThreadStart* wrapper = malloc(sizeof(ThreadStart));
        wrapper->func = matrix_worker;
        wrapper->arg = &data[t];

        handles[t] = CreateThread(NULL, 0, thread_adapter, wrapper, 0, NULL);
    }

    for (int t = 0; t < threads; ++t) {
        WaitForSingleObject(handles[t], INFINITE);
        CloseHandle(handles[t]);
    }

    free(handles);
    free(data);

#else // POSIX

    pthread_t* threads_arr = malloc(sizeof(pthread_t) * threads);
    ThreadData* data = malloc(sizeof(ThreadData) * threads);

    for (int t = 0; t < threads; ++t) {

        data[t] = (ThreadData){
            .a = a,
            .b = b_t,
            .c = c,
            .row_start = t * rows_per_thread,
            .row_end = (t == threads - 1) ? a->rows : (t + 1) * rows_per_thread
        };

        pthread_create(&threads_arr[t], NULL, matrix_worker, &data[t]);
    }

    for (int t = 0; t < threads; ++t) {
        pthread_join(threads_arr[t], NULL);
    }

    free(threads_arr);
    free(data);

#endif

    matrix_free(b_t);
    return 0;
}

int matrix_multiply_gpu(Matrix* a, Matrix* b, Matrix* c) {
    if (!a || !b || !c)
        return -1;

    gpu_matrix_multiply(a->data, b->data, c->data, a->rows, a->cols, b->cols);

    return 0;
}

int matrix_multiply(Matrix* a, Matrix* b, Matrix* c, Backend backend, int threads) {
    if (!a || !b || !c)
        return -1;

    if (backend == BACKEND_GPU)
        return matrix_multiply_gpu(a, b, c);

    return matrix_multiply_cpu_mt(a, b, c, threads);
}