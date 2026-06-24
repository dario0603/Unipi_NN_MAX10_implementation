#ifndef GUI_DEBUG_H_
#define GUI_DEBUG_H_

#include <stdio.h>

#include "../NN_lib/matrix_lib.h"

#define xDISABLE_GUI_MESSAGES
#define xGUI_TOUCH_FUNCT_DEBUG
#define GUI_NN_FUNCT_DEBUG

#ifndef DISABLE_GUI_MESSAGES

	#define GUI_PRINTF(...) 								printf(__VA_ARGS__)

	#ifdef GUI_TOUCH_FUNCT_DEBUG
		#define GUI_DEBUG_TOUCH_PRINTF(...)					printf(__VA_ARGS__)
		#define GUI_DEBUG_TOUCH_MATRIX_PRINTF(mat)			matrix_print(mat)
	#else
		#define GUI_DEBUG_TOUCH_PRINTF(...)
		#define GUI_DEBUG_TOUCH_MATRIX_PRINTF(mat)
	#endif

	#ifdef GUI_NN_FUNCT_DEBUG
		#define GUI_DEBUG_NN_PRINTF(...)					printf(__VA_ARGS__)
		#define GUI_DEBUG_NN_MATRIX_PRINTF(mat)				matrix_print(mat)
	#else
		#define GUI_DEBUG_NN_PRINTF(...)
		#define GUI_DEBUG_NN_MATRIX_PRINTF(mat)
	#endif

#else

	#define GUI_PRINTF(...)

	#define GUI_DEBUG_TOUCH_PRINTF(...)
	#define GUI_DEBUG_TOUCH_MATRIX_PRINTF(mat)

	#define GUI_DEBUG_NN_PRINTF(...)
	#define GUI_DEBUG_NN_MATRIX_PRINTF(mat)

#endif

#endif /* GUI_DEBUG_H_ */
