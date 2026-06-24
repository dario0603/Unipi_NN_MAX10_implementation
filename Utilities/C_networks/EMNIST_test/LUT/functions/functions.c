#include "debug_functions.h"
#include "functions.h"

float funct_out(float x, Funct_LUT f){

    //Check for doman validity
    if(f.xmax == f.xmin){
        DEBUG_FUNCTIONS_PRINTF("ERROR: Function domain error");
        return f.ymin;
    }

    //Check if it is out of domain
    if(x >= f.xmax)
        return f.ymax;
    if(x <= f.xmin)
        return f.ymin;

    //Convert x into index value
    float ratio = (x - f.xmin) / (f.xmax - f.xmin);
    unsigned int index = (unsigned int)(ratio * (f.lut_size - 1) + 0.5f);
    index = (index >= f.lut_size) ? f.lut_size : index;

    return f.data[index];

}
