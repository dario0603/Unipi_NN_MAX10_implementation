/*
 * symbols.h
 *
 *  Created on: 27 apr 2026
 *      Author: posta
 */

#ifndef SYMBOLS_SYMBOLS_H_
#define SYMBOLS_SYMBOLS_H_

typedef enum{

	ERASE_BUTTON_PRESSED = 0,
	ERASE_BUTTON_NOT_PRESSED = 1,
	BACKSPACE_BUTTON_PRESSED = 2,
	BACKSPACE_BUTTON_NOT_PRESSED = 3,
	PEN_BUTTON_PRESSED = 4,
	PEN_BUTTON_NOT_PRESSED = 5,

}symbol_identifier;

struct symbol_struct{
	unsigned int width;
	unsigned int height;
	unsigned int border_width;
	unsigned int border_height;
	unsigned char *pixel_data;
};

extern struct symbol_struct symbol_set[];


#endif /* SYMBOLS_SYMBOLS_H_ */
