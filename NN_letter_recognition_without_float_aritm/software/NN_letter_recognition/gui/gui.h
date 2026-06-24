/*
 * gui.h
 *
 *  Created on: 27 apr 2026
 *      Author: posta
 */

#ifndef GUI_GUI_H_
#define GUI_GUI_H_

#include <stdint.h>

#include "gui_config.h"

#include "../geometry/geometry.h"
#include "../graphic_lib/simple_graphics.h"
#include "../graphic_lib/simple_text.h"
#include "../graphic_matrix_lib/simple_graphics_matrix.h"

#include "../terasic_lib/touch_spi.h"

#include "../NN_lib/NN_lib.h"

typedef enum{

	ERASE_BUTTON = 0,
	PEN_BUTTON,
	BACKSPACE_BUTTON,
    BTN_NUM,
    BTN_NONE

}BUTTON_ID;

typedef struct{

	int Button_Index;
    RECT rcPaint;
    RECT rcButtons[BTN_NUM];
    RECT rcLetterBox[LETTER_BOX_NUM];

}DESK_INFO;

int downscale_matrix(Matrix in, Matrix *out, int dwn_fact);

/* ---------------- GUI functions ---------------- */

void GUI_init(alt_video_display *pDisplay,
			  DESK_INFO *DeskInfo, 
			  RECT *rcTouch);

int NN_Matrix_init(Matrix *in, Matrix *out, NN_f_conn *nn);

void GUI_DeskInit(alt_video_display *display, DESK_INFO *pDeskInfo);   

void GUI_DeskDraw(alt_video_display *display, DESK_INFO *pDeskInfo);

void GUI_SymbolsDraw(alt_video_display *display, DESK_INFO *pDeskInfo, int PressedButton);

int GUI_CheckButton(DESK_INFO *pDeskInfo, POINT *pt);

void GUI_ClearPaintArea(alt_video_display *pDisplay, DESK_INFO *pDeskInfo);

void GUI_ClearButtonArea(alt_video_display *pDisplay, DESK_INFO *pDeskInfo);

void GUI_ClearLetterBoxArea(alt_video_display *pDisplay, DESK_INFO *pDeskInfo);

void GUI_ClearSelectedLetter(alt_video_display *pDisplay, DESK_INFO *pDeskInfo, int letter_index);

int GUI(alt_video_display *pDisplay, 
		 TOUCH_HANDLE *pTouch, 
		 Matrix *in,
		 Matrix *out,
		 NN_f_conn *nn,
		 DESK_INFO *DeskInfo, 
		 RECT *rcTouch);

#endif /* GUI_GUI_H_ */
