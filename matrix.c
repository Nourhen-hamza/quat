#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include "matrix.h"

error_code matrix_alloc(matrix *mat, int32_t m, int32_t n) {

    // m, n
    mat -> m = m; // m lignes
    mat -> n = n; // n colonnes

    if (m < 0 || n < 0) {
        return uninitialized;
    }

    // data
    mat -> data = malloc(m * sizeof(int32_t *));

    if (mat -> data == NULL) {
        return memory_error;
    }

    for (int i = 0; i < m; ++i) {
        mat -> data[i] = malloc(n * sizeof(int32_t));
        if (mat -> data[i] == NULL) {
            matrix_destroy(mat);
            return memory_error;   
        }
    }

    return ok;
}

error_code matrix_init(matrix *mat, int32_t m, int32_t n, int32_t val) {

    error_code matrix_alloc_error = matrix_alloc(mat, m, n);

    if (matrix_alloc_error == ok) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                mat -> data[i][j] = val;
            }
        }
    }

    return matrix_alloc_error;
}

error_code matrix_destroy(matrix *mat) {

    if (mat == NULL || mat -> m < 1 || mat -> n < 1) {
      return uninitialized;
    }
    
    for (int i = 0; i < mat -> m; i++) {
      if (mat -> data[i] != NULL) {
        free(mat -> data[i]);
      } else {
        return uninitialized;
      }
    }

    if (mat -> data != NULL) {
        free(mat -> data);
        mat -> data = NULL;
    } else {
        return uninitialized;
    }

    return ok;
}

error_code matrix_init_from_array(matrix *mat, int32_t m, int32_t n, int32_t data[], int32_t s) {
    
    if (m < 0 || n < 0 || data == NULL) {
        return uninitialized;
    }

    if (s != m*n) {
        return out_of_bounds;
    }

    matrix_alloc(mat, m, n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            mat -> data[i][j] = data[j + (i*n)];
        }
    }

    return ok;
}

error_code matrix_clone(matrix *cloned, const matrix mat) {
    
    if (mat.m == -1 && mat.n == -1) {
        return uninitialized;
    }    

    matrix_alloc(cloned, mat.m, mat.n);

    for (int i = 0; i < mat.m; i++) {
        for (int j = 0; j < mat.n; j++) {
            cloned -> data[i][j] = mat.data[i][j];
        }
    }

    return ok;
}

error_code matrix_transpose(matrix *transposed, const matrix mat) {

    error_code matrix_transpose_error = matrix_alloc(transposed, mat.n, mat.m);

    if (matrix_transpose_error == ok) {
        for (int i = 0; i < transposed -> m; i++) {
            for (int j = 0; j < transposed -> n; j++) {
                transposed -> data[i][j] = mat.data[j][i];
            }
        }
    }

    return matrix_transpose_error;
}

error_code matrix_print(const matrix mat) {

    printf("Matrix : \n");
    for (int i = 0; i < mat.m; i++) {
        for (int j = 0; j < mat.n; j++) {
            printf(" %d ", mat.data[i][j]);
        }
    printf("\n");
    }

    printf("\n");

    return ok;
}

error_code matrix_extract_submatrix(matrix *sub, const matrix mat, int32_t m0, int32_t m1, int32_t n0, int32_t n1) {
    
    if (m0 < 0 || m1 >= mat.m || n0 < 0 || n1 >= mat.n || m0 > m1 || n0 > n1) {
        return out_of_bounds;
    }

    matrix_alloc(sub, (m1 - m0) + 1, (n1 - n0) + 1);

    for (int i = m0; i <= m1; i++) {
        for (int j = n0; j <= n1; j++) {
            sub -> data[i - m0][j - n0] = mat.data[i][j];
        }
    }

    return ok;
}

bool matrix_is_equal(matrix mat1, matrix mat2) {
    
    if (mat1.m != mat2.m || mat1.n != mat2.n || mat1.data == NULL || mat2.data == NULL) {
        return false;
    }

    for (int i = 0; i < mat1.m; i++) {
        for (int j = 0; j < mat1.n; j++) {
            if (mat1.data[i][j] != mat2.data[i][j]) {
               return false; 
            }
        }
    }

    return true;
}

error_code matrix_get(int32_t *elem, const matrix mat, int32_t ix, int32_t iy) {

    if (ix < 0 || iy < 0) {
        return uninitialized;
    }
    
    if (iy >= mat.m || ix >= mat.n) {
        return out_of_bounds;
    }

    *elem = mat.data[iy][ix];

    return ok;
}

error_code matrix_set(matrix mat, int32_t ix, int32_t iy, int32_t elem) {

    if (elem < 0 || ix < 0 || iy < 0) {
        return uninitialized;
    }

    if (ix >= mat.m || iy >= mat.n) {
        return out_of_bounds;
    }

    mat.data[ix][iy] = elem;
    
    return ok;
}

error_code matrix_map_ip(matrix mat, void (*foo)(int *)) {

    for (int i = 0; i < mat.m; i++) {
        for (int j = 0; j < mat.n; j++) {
            foo(&mat.data[i][j]);
        }
    }

    return ok;
}

error_code matrix_map(matrix *mapped, const matrix mat, void (*foo)(int *)) {

    matrix_clone(mapped, mat);

    for (int i = 0; i < mapped->m; i++) {
        for (int j = 0; j < mapped->n; j++) {
            foo(&mapped->data[i][j]);
        }
    }

    return ok;
}
