#ifndef MATRIX_LIB_H
#define MATRIX_LIB_H

#include <stdlib.h>

/* -------------------- Matrix -------------------- */

typedef struct{
    unsigned int row;
    unsigned int col;
    float *data;
}Matrix;

/* ---------------- Constructors ------------------ */

static inline Matrix matrix_error(void) {
    return (Matrix){0, 0, NULL};
}

Matrix matrix_init(unsigned int row, unsigned int col);

Matrix matrix_rand(unsigned int row, unsigned int col, float min, float max);

Matrix matrix_identity(unsigned int dim);

Matrix matrix_fill(unsigned int row, unsigned int col, float val);

Matrix matrix_null(unsigned int row, unsigned int col);

/* ---------------- Operations -------------------- */

void matrix_assign(Matrix *a, const Matrix b);

int matrix_flatten(Matrix *flattened, const Matrix m, int one_col);

int matrix_copy_data(Matrix *a, const Matrix b);

int matrix_multiply(Matrix *a, Matrix *b, Matrix *result);

int matrix_sum(Matrix *a, Matrix *b, Matrix *result);

void matrix_transpose(Matrix *m);

int matrix_valid(Matrix *m);

int matrix_compare(Matrix *a, Matrix *b);

void matrix_fill_values(Matrix *m, float val);

void matrix_clear_values(Matrix *m);

void matrix_print(Matrix *m);

/* ----------------- Destructors ------------------- */

void matrix_free(Matrix *m);

#endif /* MATRIX_LIB_H */
