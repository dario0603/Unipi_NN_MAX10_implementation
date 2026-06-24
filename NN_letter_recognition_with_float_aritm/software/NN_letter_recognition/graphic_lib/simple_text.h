#ifndef VIP_TEXT_H_
#define VIP_TEXT_H_

#include "alt_video_display.h"
#include "../LUT/fonts/fonts.h"
#include "../LUT/symbols/symbols.h"


int vid_print_string_alpha(int horiz_offset, int vert_offset, int color, int background_color, struct abc_font_struct font[], alt_video_display * display, char string[], int invert_colors, int rotate);
int vid_print_char_alpha (int horiz_offset, int vert_offset, int color, char character, int background_color, struct abc_font_struct font[], alt_video_display * display, int invert_colors, int rotate);
int vid_print_symbol_alpha (int horiz_offset, int vert_offset, int color, int background_color, symbol_identifier id_sym, struct symbol_struct symbol[], alt_video_display * display, int invert_colors, int rotate);
int vid_print_matrix_alpha (int horiz_offset, int vert_offset, int color, int background_color, unsigned char *m, unsigned int row, unsigned int col, alt_video_display * display, int invert_colors, int rotate);

#endif /*VIP_TEXT_H_*/
