//System library include
#include "system.h"

//Gui library
#include "../gui/gui.h"
#include "../gui/gui_config.h"

//Touch screen library
#include "../terasic_lib/touch_spi.h"

//Altera display library
#include "../graphic_lib/alt_video_display.h"

//NN library
#include "../NN_lib/matrix_lib.h"
#include "../NN_lib/NN_lib.h"

int main(void){

	//init display
	alt_video_display Display = {
	    .interlace = 0,
        .bytes_per_pixel = 2,
        .color_depth = 16,
        .height = SCREEN_HEIGHT,
        .width = SCREEN_WIDTH,	
    };

    //init touch
	TOUCH_HANDLE *pTouch;
    pTouch = Touch_Init(TOUCH_PANEL_SPI_BASE, TOUCH_PANEL_PEN_IRQ_N_BASE, TOUCH_PANEL_PEN_IRQ_N_IRQ);
    if(!pTouch){
        printf("Failed to init touch\r\n");
        return 0;       //Exit failure
    }        
    printf("Init touch successfully\r\n");

    //init LCD
    DESK_INFO DeskInfo;
    RECT rcTouch;
    GUI_init(&Display, &DeskInfo, &rcTouch);

    //init neural network
    Matrix in, out;
    NN_f_conn nn;
    int status = NN_Matrix_init(&in, &out, &nn);

    if(status == 1){
        #ifdef MNIST_DATASET
            printf("MNIST DATASET loaded\r\n");
        #else
            printf("EMNIST DATASET loaded\r\n");
        #endif
    }else{
        #ifdef MNIST_DATASET
            printf("Error loading MNIST DATASET\r\n");
        #else
            printf("Error loading EMNIST DATASET\r\n");
        #endif
    };

    if(status == 1)
        //Print gui
        status = GUI(&Display, pTouch, &in, &out, &nn, &DeskInfo, &rcTouch);

    //Deallocate matrix from dynamic memory
	matrix_free(&in);
	matrix_free(&out);
	NN_free(&nn);

    return status;       //Exit status

}
