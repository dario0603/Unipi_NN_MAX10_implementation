#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct {
    unsigned int lut_size;
    float xmin;
    float xmax;
    float ymin;
    float ymax;
    float *data;
} Funct_LUT;

float funct_out(float x, Funct_LUT f);

extern Funct_LUT sigmoid_fn;
extern Funct_LUT tanh_fn;

#endif /* FUNCTIONS_H */
