#ifndef MATRIX_H
#define MATRIX_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

typedef enum _error_code {
    ok, out_of_bounds, memory_error, uninitialized
} error_code;

typedef struct _matrix {
    int32_t m, n; // ligne et colone
    int32_t **data;
} matrix;

error_code matrix_alloc(matrix *mat, int32_t m, int32_t n);
error_code matrix_init(matrix *mat, int32_t m, int32_t n, int32_t val);
error_code matrix_destroy(matrix *mat);
error_code matrix_init_from_array(matrix *mat, int32_t m, int32_t n, int32_t data[], int32_t s);
error_code matrix_clone(matrix *cloned, const matrix mat);
error_code matrix_transpose(matrix *transposed, const matrix mat);
error_code matrix_print(const matrix mat);
error_code matrix_extract_submatrix(matrix *sub, const matrix mat, int32_t m0, int32_t m1, int32_t n0, int32_t n1);
bool matrix_is_equal(matrix mat1, matrix mat2);
error_code matrix_get(int32_t *elem, const matrix mat, int32_t ix, int32_t iy);
error_code matrix_set(matrix mat, int32_t ix, int32_t iy, int32_t elem);
error_code matrix_map_ip(matrix mat, void (*foo)(int *));
error_code matrix_map(matrix *mapped, const matrix mat, void (*foo)(int *));

#endif