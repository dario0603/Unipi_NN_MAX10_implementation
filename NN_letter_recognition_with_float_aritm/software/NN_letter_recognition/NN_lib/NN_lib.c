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

    nn.w1 = matrix_init(WEIGHT_AND_BIAS[WEIGHT_NN_1].row, WEIGHT_AND_BIAS[WEIGHT_NN_1].col);
    nn.b1 = matrix_init(1, WEIGHT_AND_BIAS[BIAS_NN_1].col);

    nn.w2 = matrix_init(WEIGHT_AND_BIAS[WEIGHT_NN_2].row, WEIGHT_AND_BIAS[WEIGHT_NN_2].col);
    nn.b2 = matrix_init(1, WEIGHT_AND_BIAS[BIAS_NN_2].col);

    nn.w3 = matrix_init(WEIGHT_AND_BIAS[WEIGHT_NN_3].row, WEIGHT_AND_BIAS[WEIGHT_NN_3].col);
    nn.b3 = matrix_init(1, WEIGHT_AND_BIAS[BIAS_NN_3].col);
  
    //Copy weights and biases inside w# and b# matrix
    matrix_copy_data(&nn.w1, WEIGHT_AND_BIAS[WEIGHT_NN_1]);
    matrix_copy_data(&nn.b1, WEIGHT_AND_BIAS[BIAS_NN_1]);

    matrix_copy_data(&nn.w2, WEIGHT_AND_BIAS[WEIGHT_NN_2]);
    matrix_copy_data(&nn.b2, WEIGHT_AND_BIAS[BIAS_NN_2]);

    matrix_copy_data(&nn.w3, WEIGHT_AND_BIAS[WEIGHT_NN_3]);
    matrix_copy_data(&nn.b3, WEIGHT_AND_BIAS[BIAS_NN_3]);

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
*  Purpose: save into *out matrix the output response at
*  			certain inputs
*
******************************************************************/

int forw_prop(Matrix input, Matrix *out, NN_f_conn *nn, void (*activation_funct)(Matrix *a)){

    Matrix err = matrix_error();
	int status = 1;		//Exit status

    //Verify that input vector has the right dimension
    if(input.col != (*nn).w1.row){
        DEBUG_NN_PRINTF("ERROR: Input vector has not compatible dimension input:%d expected:%d \n", input.col, (*nn).w1.col);
        return 0;		//Exit failure
    }

    //Instantiate temporary matrix
    Matrix tmp = matrix_init(1, 1);

    //Check matrix
    if((status == 1) && (matrix_compare(&tmp, &err) == 1))
    	status = 0;		//Failure status
    if((status == 1) && (matrix_compare(out, &err) == 1))
    	status = 0;		//Failure status

    if((status == 1) && (matrix_multiply(&input, &(*nn).w1, &tmp) == 0))
    	status = 0;		//Failure status

    if((status == 1) && (matrix_sum(&tmp, &(*nn).b1, out) == 0))
    	status = 0;		//Failure status
    
    if(status == 1){
		//Relu cost function
		relu_funct(out);

		DEBUG_NN_MATRIX_PRINTF(out);
    }

    if((status == 1) && (matrix_multiply(out, &(*nn).w2, &tmp) == 0))
    	status = 0;		//Failure status

    if((status == 1) && (matrix_sum(&tmp, &(*nn).b2, out) == 0))
    	status = 0;		//Failure status
    
    if(status == 1){
		//Relu cost function
		relu_funct(out);

		DEBUG_NN_MATRIX_PRINTF(out);
    }

    if((status == 1) && (matrix_multiply(out, &(*nn).w3, &tmp) == 0))
    	status = 0;		//Failure status

    if((status == 1) && (matrix_sum(&tmp, &(*nn).b3, out) == 0))
    	status = 0;		//Failure status
    
    if(status == 1)
		DEBUG_NN_MATRIX_PRINTF(out);

    //Deallocate temporary Matrix
    matrix_free(&tmp);

    return status;

}

/******************************************************************
*  Function: normalize_matrix
*
*  Purpose: Convert the grayscale matrix input into neural network
*           compatible matrix (float values)
*
******************************************************************/

int normalize_matrix(unsigned int *grayscale_m, unsigned int row, unsigned int col, Matrix *m){

	Matrix err = matrix_error();

	matrix_free(m);
    (*m) = matrix_init(row, col);

    //Check for the correct generation of matrix
    if(matrix_compare(m, &err) == 1)
        return 0;	//Exit failure

    for(unsigned long int i=0; i<(row*col); i++)
        (*m).data[i] = (float)(grayscale_m[i] && 0xffu) / 255.0f;

    return 1;	//Exit success

}

/******************************************************************
*  Function: emnist_output_convert
*
*  Purpose: Return the corresponding character from the output of
*           neural network.
*
******************************************************************/

const static char emnist_byclass_map[62] = {
    '0','1','2','3','4','5','6','7','8','9',
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z',
    'a','b','c','d','e','f','g','h','i','j',
    'k','l','m','n','o','p','q','r','s','t',
    'u','v','w','x','y','z'
};

char emnist_output_convert(Matrix input){

    float max_val = input.data[0];
    unsigned long int max_val_index = 0;

    if((input.col != 62) || (input.row != 1)){
        DEBUG_NN_PRINTF("ERROR: Incorrect output vector dimensions \n");
        DEBUG_NN_PRINTF("Expected r:1 c:62 actual r:%d c:%d \n", input.row, input.col);
        return 62;
    }

    for(unsigned long int i=0; i<(input.row*input.col); i++){
        if(input.data[i] > max_val){
            max_val = input.data[i];
            max_val_index = i;
        }
    }

    return emnist_byclass_map[max_val_index];

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

char nn_output_convert(Matrix input){
	#ifdef MNIST_DATASET
		return mnist_output_convert(input);
	#else
		return emnist_output_convert(input);
	#endif
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

/******************************************************************
*  Function: NN_free
*
*  Purpose: Deallocate all matrix from dynamic memory
*
******************************************************************/

void NN_free(NN_f_conn *nn){

	matrix_free(&(*nn).w1);
	matrix_free(&(*nn).b1);

	matrix_free(&(*nn).w2);
	matrix_free(&(*nn).b2);

	matrix_free(&(*nn).w3);
	matrix_free(&(*nn).b3);

}
