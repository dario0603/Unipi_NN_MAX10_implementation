#ifndef _WEIGHT_AND_BIAS_H_
#define _WEIGHT_AND_BIAS_H_

#include "../../NN_lib/matrix_lib.h"

//Comment this line to consider regular weight matrix instead of transposed ones
#define xTRANSPOSED_WEIGHT_MATRIX
//Comment this line to use EMNIST dataset (letters and numbers) instead of MNIST (only numbers)
#define xMNIST_DATASET

typedef enum{
    
    WEIGHT_NN_1 = 0,
    BIAS_NN_1 = 3,

    WEIGHT_NN_2 = 1,
    BIAS_NN_2 = 4,

    WEIGHT_NN_3 = 2,
    BIAS_NN_3 = 5,

}NN_weight_index;

#ifdef MNIST_DATASET
	#define WEIGHT_AND_BIAS weight_and_bias_mnist
	extern Matrix weight_and_bias_mnist[6];
#else
	#define WEIGHT_AND_BIAS weight_and_bias_emnist
	extern Matrix weight_and_bias_emnist[6];
#endif

#endif /* _WEIGHT_AND_BIAS_H_ */
