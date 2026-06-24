#ifndef DEBUG_GRAPHIC_LIB_H
#define DEBUG_GRAPHIC_LIB_H

#include <stdio.h>

#include "../NN_lib/matrix_lib.h"

#define GRAPHIC_LIB_DEBUG

#ifdef GRAPHIC_LIB_DEBUG
	#define GRAPHIC_LIB_PRINTF(...)		printf(__VA_ARGS__)
	#define GRAPHIC_LIB_MATRIX_PRINTF(mat)		matrix_print(mat)
#else 
	#define GRAPHIC_LIB_PRINTF(...)
	#define GRAPHIC_LIB_MATRIX_PRINTF(mat)
#endif

#endif /* DEBUG_GRAPHIC_LIB_H */