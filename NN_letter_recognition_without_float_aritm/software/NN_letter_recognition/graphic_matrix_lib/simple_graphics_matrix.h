#ifndef __SIMPLE_GRAPHICS_MATRIX_H__
#define __SIMPLE_GRAPHICS_MATRIX_H__

#include "../NN_lib/matrix_lib.h"
#include "../graphic_lib/alt_video_display.h"

int vid_draw_line_on_matrix(int horiz_start, int vert_start, 
                             int horiz_end, int vert_end, 
                             int width, 
                             int color, 
                             alt_video_display* display, 
                             Matrix *m);

int vid_draw_horiz_line_on_matrix(short Hstart, short Hend, 
                                   int V, 
                                   int color, 
                                   alt_video_display* display, 
                                   Matrix *m);

int vid_draw_sloped_line_on_matrix( unsigned short horiz_start,
                                     unsigned short vert_start,
                                     unsigned short horiz_end,
                                     unsigned short vert_end,
                                     unsigned short width,
                                     int color,
                                     alt_video_display* display, 
                                     Matrix *m);


int vid_draw_circle_on_matrix(int Hcenter, 
                               int Vcenter, 
                               int radius, 
                               int color, 
                               char fill, 
                               alt_video_display* display, 
                               Matrix *m);


int vid_round_corner_points_on_matrix( int cx, int cy, 
                                        int x, int y,
                                        int straight_width, int straight_height, 
                                        int color,
                                        char fill, 
                                        alt_video_display* display, 
                                        Matrix *m);

int vid_set_pixel_on_matrix(int horiz, int vert, 
                             unsigned int color, 
                             alt_video_display* display, 
                             Matrix *m);

#endif
