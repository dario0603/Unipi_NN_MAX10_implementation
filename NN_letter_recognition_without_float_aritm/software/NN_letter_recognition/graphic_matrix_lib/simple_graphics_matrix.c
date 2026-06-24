/*
 * my_simple_graphics.c
 *
 *  Created on: 14 mag 2026
 *      Author: Tonarini Tommaso
 */


#include "simple_graphics_matrix.h"
#include "debug_graphic_lib.h"

#include "../gui/gui_config.h"
#include "../NN_lib/matrix_lib.h"
#include "../graphic_lib/simple_graphics.h"

#define xSAVING_PIXEL_X_MIRRORED
#define SAVING_PIXEL_Y_MIRRORED

int save_pixel_to_matrix(alt_video_display *display, int x, int y, Matrix *m)
{
	
	if(((*m).row < DRAW_RECT_WIDTH)||((*m).col < DRAW_RECT_HEIGHT)){
		GRAPHIC_LIB_PRINTF("ERROR: Matrix inserted in 'save pixel to matrix' function too small \n");
		GRAPHIC_LIB_PRINTF("LCD dimensions x:%d y:%d matrix values r:%d c:%d", DRAW_RECT_HEIGHT, DRAW_RECT_WIDTH, (*m).row, (*m).col);
		return 0;	//Exit failure
	}

	//the matrix starts in the top right corner when viewing the LT24 writing on the board in the correct orientation
	x = x - ((display->width) - DRAW_DIST_FROM_RIGHT - DRAW_RECT_HEIGHT);
	y = y - ((display->height) - DRAW_DIST_FROM_BOTTOM - DRAW_RECT_WIDTH);

    if ((x >= 0) && (x < (*m).row) && (y >= 0) && (y < (*m).col)){

		#ifdef SAVING_PIXEL_X_MIRRORED
    		x = (*m).row - x;
		#endif

		#ifdef SAVING_PIXEL_Y_MIRRORED
    		y = (*m).col - y;
		#endif

		//Matrix indexing syntax
		//m[ column * row_length + row ] -> m[row][column]

    	(*m).data[x*(*m).row + y] = 1.0f;

		return 1;		//Exit success

    }else{

    	GRAPHIC_LIB_PRINTF("ERROR: Set pixel to matrix dimension error \n");
    	GRAPHIC_LIB_PRINTF("Input coordinate x:%d y:%d maximum values x:%d y:%d", x, y, (*m).row, (*m).col);
		return 0;	//Exit failure

	}
}

int vid_draw_line_on_matrix(int horiz_start, int vert_start, int horiz_end, int vert_end, int width, int color, alt_video_display* display, Matrix *m)
{

	unsigned int status;

	if( vert_start == vert_end )
	{
		status = vid_draw_horiz_line_on_matrix( (unsigned short)horiz_start,
		                     (unsigned short)horiz_end,
		                     (unsigned short)vert_start,
		                     color,
		                     display, 
							 m);
	}
	else
	{
		status = vid_draw_sloped_line_on_matrix( (unsigned short)horiz_start,
		                      (unsigned short)vert_start,
		                      (unsigned short)horiz_end,
		                      (unsigned short)vert_end,
		                      (unsigned short)width,
		                      color,
		                      display,
							  m);
	}

	return status;

}

int vid_draw_horiz_line_on_matrix(short Hstart, short Hend, int V, int color, alt_video_display* display, Matrix *m)
{
	unsigned int status = 0;

	int x;
	for(x=Hstart; x<Hend; x++) {
		status |= vid_set_pixel_on_matrix(x, V, color, display, m);
	}

	return status;

}

int vid_draw_sloped_line_on_matrix( unsigned short horiz_start,
                           unsigned short vert_start,
                           unsigned short horiz_end,
                           unsigned short vert_end,
                           unsigned short width,
                           int color,
                           alt_video_display* display,
						   Matrix *m)
{

	unsigned int status = 0;

	// Find the vertical and horizontal distance between the two points
	int horiz_delta = abs(horiz_end-horiz_start);
	int vert_delta = abs(vert_end-vert_start);

	// Find out what direction we are going
	int horiz_incr, vert_incr;
	if (horiz_start > horiz_end) {
		horiz_incr=-1;
	}
	else {
		horiz_incr=1;
	}
	if (vert_start > vert_end) {
		vert_incr=-1;
	}
	else {
		vert_incr=1;
	}

	// Find out which axis is always incremented when drawing the line
	// If it's the horizontal axis
	if (horiz_delta >= vert_delta) {
		int dPr   = vert_delta<<1;
		int dPru  = dPr - (horiz_delta<<1);
		int P     = dPr - horiz_delta;

		// Process the line, one horizontal point at at time
		for (; horiz_delta >= 0; horiz_delta--) {
			status |= vid_draw_circle_on_matrix(horiz_start, vert_start, width, color, DO_FILL, display, m);
			
			//If we're moving both up and right
			if (P > 0) {
				horiz_start+=horiz_incr;
				vert_start+=vert_incr;
				P+=dPru;
			} else {
				horiz_start+=horiz_incr;
				P+=dPr;
			}
		}
		// If it's the vertical axis
	} else {
		int dPr   = horiz_delta<<1;
		int dPru  = dPr - (vert_delta<<1);
		int P     = dPr - vert_delta;

		// Process the line, one vertical point at at time
		for (; vert_delta>=0; vert_delta--) {
			
			status |= vid_draw_circle_on_matrix(horiz_start, vert_start, width, color, DO_FILL, display, m);
			
			if (P > 0) {
				horiz_start+=horiz_incr;
				vert_start+=vert_incr;
				P+=dPru;
			} else {
				vert_start+=vert_incr;
				P+=dPr;
			}
		}
	}

	return status;

}

int vid_draw_circle_on_matrix(int Hcenter, int Vcenter, int radius, int color, char fill, alt_video_display* display, Matrix *m)
{

	unsigned int status = 0;		//Mantain the status (Success or Failure of the operation)

	int x = 0;
	int y = radius;
	int p = (5 - radius*4)/4;

	// Start the circle with the top, bottom, left, and right pixels.
	vid_round_corner_points(Hcenter, Vcenter, x, y, 0, 0, color, fill, display);
	status |= save_pixel_to_matrix(display, Hcenter+x, Vcenter+y, m);

	// Now start moving out from those points until the lines meet
	while (x < y) {
		x++;
		if (p < 0) {
			p += 2*x+1;
		} else {
			y--;
			p += 2*(x-y)+1;
		}
		status |= vid_round_corner_points_on_matrix(Hcenter, Vcenter, x, y, 0, 0, color, fill, display, m);
	}

	return status;

}

int vid_round_corner_points_on_matrix( int cx, int cy, int x, int y,
                              int straight_width, int straight_height, int color,
                              char fill, alt_video_display* display, Matrix *m)
{

	unsigned int status = 0;		//Mantain the status (Success or Failure of the operation)

	// If we're directly above, below, left and right of center (0 degrees), plot those 4 pixels
	if (x == 0) {
		// bottom
		status |= vid_set_pixel_on_matrix(cx, cy + y + straight_height, color, display, m);
		status |= vid_set_pixel_on_matrix(cx + straight_width, cy + y + straight_height, color, display, m);
		// top
		status |= vid_set_pixel_on_matrix(cx, cy - y, color, display, m);
		status |= vid_set_pixel_on_matrix(cx + straight_width, cy - y, color, display, m);

		if(fill) {
			status |= vid_draw_line_on_matrix(cx - y, cy, cx + y + straight_width, cy, 1, color, display, m);
			status |= vid_draw_line_on_matrix(cx - y, cy + straight_height, cx + y + straight_width, cy + straight_height, 1, color, display, m);
		} else {
			//right
			status |= vid_set_pixel_on_matrix(cx + y + straight_width, cy, color, display, m);
			status |= vid_set_pixel_on_matrix(cx + y + straight_width, cy + straight_height, color, display, m);
			//left
			status |= vid_set_pixel_on_matrix(cx - y, cy, color, display, m);
			status |= vid_set_pixel_on_matrix(cx - y, cy + straight_height, color, display, m);
		}

	}else{
		// If we've reached the 45 degree points (x=y), plot those 4 pixels
		if (x == y) {
			if(fill) {
				status |= vid_draw_line_on_matrix(cx - x, cy + y + straight_height, cx + x + straight_width, cy + y + straight_height, 1, color, display, m); // lower
				status |= vid_draw_line_on_matrix(cx - x, cy - y, cx + x + straight_width, cy - y, 1, color, display, m); // upper

			} else {
				status |= vid_set_pixel_on_matrix(cx + x + straight_width, cy + y + straight_height, color, display, m); // bottom right
				status |= vid_set_pixel_on_matrix(cx - x, cy + y + straight_height, color, display, m); // bottom left
				status |= vid_set_pixel_on_matrix(cx + x + straight_width, cy - y, color, display, m); // top right
				status |= vid_set_pixel_on_matrix(cx - x, cy - y, color, display, m); // top left
			}
		}else{
			// If we're between 0 and 45 degrees plot 8 pixels.
			if (x < y) {
				if(fill) {
					status |= vid_draw_line_on_matrix(cx - x, cy + y + straight_height, cx + x + straight_width, cy + y + straight_height, 1, color, display, m);
					status |= vid_draw_line_on_matrix(cx - y, cy + x + straight_height, cx + y + straight_width, cy + x + straight_height, 1, color, display, m);
					status |= vid_draw_line_on_matrix(cx - y, cy - x, cx + y + straight_width, cy - x, 1, color, display, m);
					status |= vid_draw_line_on_matrix(cx - x, cy - y, cx + x + straight_width, cy - y, 1, color, display, m);
				} else {
					status |= vid_set_pixel_on_matrix(cx + x + straight_width, cy + y + straight_height, color, display, m);
					status |= vid_set_pixel_on_matrix(cx - x, cy + y + straight_height, color, display, m);
					status |= vid_set_pixel_on_matrix(cx + x + straight_width, cy - y, color, display, m);
					status |= vid_set_pixel_on_matrix(cx - x, cy - y, color, display, m);
					status |= vid_set_pixel_on_matrix(cx + y + straight_width, cy + x + straight_height, color, display, m);
					status |= vid_set_pixel_on_matrix(cx - y, cy + x + straight_height, color, display, m);
					status |= vid_set_pixel_on_matrix(cx + y + straight_width, cy - x, color, display, m);
					status |= vid_set_pixel_on_matrix(cx - y, cy - x, color, display, m);
				}
			}
		}
	}

	return status;

}

int vid_set_pixel_on_matrix(int horiz, int vert, unsigned int color, alt_video_display* display, Matrix *m){

	unsigned int color16;

	// encode from RGB 24 to RGB  5 6 5

	color16 = (color & 0xFF) >> 3; // blue
	color16 |= (color & 0xFC00) >> 5; // green
	color16 |= (color & 0xF80000) >> 8; // red

	LCD_DrawPoint(horiz, vert, color16);

	if(save_pixel_to_matrix(display, horiz, vert, m) == 1)	//enable pixel saving on matrix
		return 1;	//Exit success
	else
		return 0;	//Exit failure
	
}
