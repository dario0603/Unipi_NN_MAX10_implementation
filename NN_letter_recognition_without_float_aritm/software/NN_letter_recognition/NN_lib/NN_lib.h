#ifndef NN_LIB_H
#define NN_LIB_H

#include <stdlib.h>

#include "matrix_lib.h"
#include "../LUT/weight_and_bias/weight_and_bias.h"
#include "../LUT/functions/functions.h"

typedef struct{
    
    Matrix w1;
    Matrix b1;

    Matrix w2;
    Matrix b2;

    Matrix w3;
    Matrix b3;

}NN_f_conn;

/* ---------------- Constructors ------------------ */

NN_f_conn NN_init(void);

/* ---------------- Operations -------------------- */

int forw_prop(Matrix input, Matrix *out, NN_f_conn *nn, void (*activation_funct)(Matrix *a));

int normalize_matrix(unsigned int *grayscale_m, unsigned int row, unsigned int col, Matrix *m);

//char emnist_output_convert(Matrix input);

//char mnist_output_convert(Matrix input);

char nn_output_convert(Matrix input);

/* ------------- Activation functions ------------- */

void relu_funct(Matrix *a);

void leaky_relu_funct(Matrix *a);

void tanh_funct(Matrix *a);

void sigmoid_funct(Matrix *a);

/* ----------------- Destructors ------------------- */

void NN_free(NN_f_conn *nn);

#endif /* NN_LIB_H */
