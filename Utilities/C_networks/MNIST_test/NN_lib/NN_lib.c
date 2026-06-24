#include <stdlib.h>
#include <stdio.h>

#include "NN_lib_debug.h"
#include "NN_lib.h"
#include "matrix_lib.h"

/******************************************************************
*  Function: NN_init
*
*  Purpose: Initialize the neural network
*
******************************************************************/

NN_f_conn NN_init(void){

    NN_f_conn nn;

    //Matrix initializations

    #ifdef TRANSPOSED_WEIGHT_MATRIX
        nn.x = matrix_init(1, weight_and_bias[WEIGHT_NN_1].col);
    #else
        nn.x = matrix_init(1, weight_and_bias[WEIGHT_NN_1].row);
    #endif

    nn.w1 = matrix_init(weight_and_bias[WEIGHT_NN_1].row, weight_and_bias[WEIGHT_NN_1].col);
    nn.b1 = matrix_init(1, weight_and_bias[BIAS_NN_1].col);
    nn.a1 = matrix_init(1, weight_and_bias[BIAS_NN_1].col);

    nn.w2 = matrix_init(weight_and_bias[WEIGHT_NN_2].row, weight_and_bias[WEIGHT_NN_2].col);
    nn.b2 = matrix_init(1, weight_and_bias[BIAS_NN_2].col);
    nn.a2 = matrix_init(1, weight_and_bias[BIAS_NN_2].col);

    nn.w3 = matrix_init(weight_and_bias[WEIGHT_NN_3].row, weight_and_bias[WEIGHT_NN_3].col);
    nn.b3 = matrix_init(1, weight_and_bias[BIAS_NN_3].col);
    nn.a3 = matrix_init(1, weight_and_bias[BIAS_NN_3].col);

    nn.y = matrix_init(1, weight_and_bias[BIAS_NN_3].col);
  
    //Copy weights and biases inside w# and b# matrix
    matrix_copy_data(&nn.w1, weight_and_bias[WEIGHT_NN_1]);
    matrix_copy_data(&nn.b1, weight_and_bias[BIAS_NN_1]);

    matrix_copy_data(&nn.w2, weight_and_bias[WEIGHT_NN_2]);
    matrix_copy_data(&nn.b2, weight_and_bias[BIAS_NN_2]);

    matrix_copy_data(&nn.w3, weight_and_bias[WEIGHT_NN_3]);
    matrix_copy_data(&nn.b3, weight_and_bias[BIAS_NN_3]);

    #ifdef TRANSPOSED_WEIGHT_MATRIX

        matrix_transpose(&nn.w1);
        matrix_transpose(&nn.w2);
        matrix_transpose(&nn.w3);

    #endif

    return nn;

}

/******************************************************************
*  Function: forw_prop
*
*  Purpose: Return the output response at certain inputs
*
******************************************************************/

Matrix forw_prop(Matrix input, NN_f_conn *nn, void (*activation_funct)(Matrix *a)){
    
    //Verify that input vector has the right dimension
    if(input.col != (*nn).x.col){
        DEBUG_NN_PRINTF("ERROR: Input vector has not compatible dimension input:%d expected:%d \n", input.col, (*nn).x.col);
        return matrix_error();
    }

    //Do the computation
    Matrix tmp1 = matrix_init(1, 1);
    Matrix tmp2 = matrix_init(1, 1);

    if(matrix_multiply(&input, &(*nn).w1, &tmp1) == 0)
        return matrix_error();

    if(matrix_sum(&tmp1, &(*nn).b1, &tmp2) == 0)
        return matrix_error();
    
    //Relu cost function
    relu_funct(&tmp2);

    DEBUG_NN_MATRIX_PRINTF(&tmp2);

    if(matrix_multiply(&tmp2, &(*nn).w2, &tmp1) == 0)
        return matrix_error();

    if(matrix_sum(&tmp1, &(*nn).b2, &tmp2) == 0)
        return matrix_error();
    
    //Relu cost function
    relu_funct(&tmp2);

    DEBUG_NN_MATRIX_PRINTF(&tmp2);

    if(matrix_multiply(&tmp2, &(*nn).w3, &tmp1) == 0)
        return matrix_error();

    if(matrix_sum(&tmp1, &(*nn).b3, &tmp2) == 0)
        return matrix_error();
    
    DEBUG_NN_MATRIX_PRINTF(&tmp2);

    return tmp2;

}

/******************************************************************
*  Function: normalize_matrix
*
*  Purpose: Convert the grayscale matrix input into neural network
*           compatible matrix (float values)
*
******************************************************************/

Matrix normalize_matrix(unsigned int *grayscale_m, unsigned int row, unsigned int col){

    Matrix m = matrix_init(row, col);

    //Check for the correct generation of matrix
    Matrix err = matrix_error();
    if(matrix_compare(&m, &err) == 1)
        return matrix_error();

    for(unsigned long int i=0; i<(row*col); i++)
        m.data[i] = (grayscale_m[i] && 0xffu) / 255;

    return m;

}

/******************************************************************
*  Function: mnist_output_convert
*
*  Purpose: Return the corresponding character from the output of
*           neural network.
*
******************************************************************/

const static char mnist_byclass_map[10] = {
    '0','1','2','3','4','5','6','7','8','9',
};

char mnist_output_convert(Matrix input){

    float max_val = input.data[0];
    unsigned long int max_val_index = 0;

    if((input.col != 10) || (input.row != 1)){
        DEBUG_NN_PRINTF("ERROR: Incorrect output vector dimensions \n");
        DEBUG_NN_PRINTF("Expected r:1 c:10 actual r:%d c:%d \n", input.row, input.col);
        return 10;
    }

    for(unsigned long int i=0; i<(input.row*input.col); i++){
        if(input.data[i] > max_val){
            max_val = input.data[i];
            max_val_index = i;
        }
    }

    return mnist_byclass_map[max_val_index];

}

/******************************************************************
*  Function: relu_funct
*
*  Purpose: Return the relu modifyed input
*
******************************************************************/

void relu_funct(Matrix *a){

    for(unsigned long int i=0; i<((*a).row*(*a).col); i++)
        if((*a).data[i] < 0)
            (*a).data[i] = 0;

}

/******************************************************************
*  Function: leaky_relu_funct
*
*  Purpose: Return the leaky_relu modifyed input
*
******************************************************************/

void leaky_relu_funct(Matrix *a){

    for(unsigned long int i=0; i<((*a).row*(*a).col); i++)
        if((*a).data[i] < 0)
            (*a).data[i] = 0.1*(*a).data[i];

}

/******************************************************************
*  Function: tanh_funct
*
*  Purpose: Return the tanh modifyed input
*
******************************************************************/

void tanh_funct(Matrix *a){

    for(unsigned long int i=0; i<((*a).row*(*a).col); i++)
        (*a).data[i] = funct_out((*a).data[i], tanh_fn);

}

/******************************************************************
*  Function: sigmoid_funct
*
*  Purpose: Return the sigmoid modifyed input
*
******************************************************************/

void sigmoid_funct(Matrix *a){
    
    for(unsigned long int i=0; i<((*a).row*(*a).col); i++)
        (*a).data[i] = funct_out((*a).data[i], sigmoid_fn);

}