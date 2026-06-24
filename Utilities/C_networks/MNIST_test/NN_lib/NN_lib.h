#ifndef NN_LIB_H
#define NN_LIB_H

#include <stdlib.h>

#include "matrix_lib.h"
#include "../LUT/weight_and_bias/weight_and_bias.h"
#include "../LUT/functions/functions.h"

typedef struct {

    Matrix x;
    
    Matrix w1;
    Matrix b1;
    Matrix a1;

    Matrix w2;
    Matrix b2;
    Matrix a2;

    Matrix w3;
    Matrix b3;
    Matrix a3;

    Matrix y;

}NN_f_conn;

/* ---------------- Constructors ------------------ */

NN_f_conn NN_init(void);

/* ---------------- Operations -------------------- */

Matrix forw_prop(Matrix input, NN_f_conn *nn, void (*activation_funct)(Matrix *a));

Matrix normalize_matrix(unsigned int *grayscale_m, unsigned int row, unsigned int col);

char mnist_output_convert(Matrix input);

/* ------------- Activation functions ------------- */

void relu_funct(Matrix *a);

void leaky_relu_funct(Matrix *a);

void tanh_funct(Matrix *a);

void sigmoid_funct(Matrix *a);

#endif /* NN_LIB_H */