#ifndef NN_LIB_DEBUG_H
#define NN_LIB_DEBUG_H

#include <stdio.h>

#include "matrix_lib.h"

//Comment this line to disable debugging messages
#define NN_LIB_DEBUG
#define MATRIX_LIB_DEBUG

#ifdef MATRIX_LIB_DEBUG
	#define DEBUG_MATRIX_PRINTF(...)		printf(__VA_ARGS__)
#else 
	#define DEBUG_MATRIX_PRINTF(...)
#endif

#ifdef NN_LIB_DEBUG
	#define DEBUG_NN_PRINTF(...)			printf(__VA_ARGS__)
	#define DEBUG_NN_MATRIX_PRINTF(mat)		matrix_print(mat)
#else 
	#define DEBUG_NN_PRINTF(...)
	#define DEBUG_NN_MATRIX_PRINTF(mat)
#endif

#endif /* NN_LIB_DEBUG_H */