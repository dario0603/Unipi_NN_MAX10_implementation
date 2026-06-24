#ifndef WEIGHT_AND_BIAS
#define WEIGHT_AND_BIAS

#include "../../NN_lib/matrix_lib.h"

//Comment this line to consider regular weight matrix instead of transposed ones
//#define TRANSPOSED_WEIGHT_MATRIX

typedef enum{
    
    WEIGHT_NN_1 = 0,
    BIAS_NN_1 = 3,

    WEIGHT_NN_2 = 1,
    BIAS_NN_2 = 4,

    WEIGHT_NN_3 = 2,
    BIAS_NN_3 = 5,

}NN_weight_index;

extern Matrix weight_and_bias[];

#endif /* WEIGHT_AND_BIAS */