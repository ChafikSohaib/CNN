#ifndef CONVOLUTION_H
#define CONVOLUTION_H


#include "types.h"

void convolution(coef_type matrice[9], image_type image_in[IMAGE_HEIGHT*IMAGE_WIDTH], image_type image_out[IMAGE_HEIGHT*IMAGE_WIDTH]);  
void multi_convolution(coef_type coeffs[NB_COEFFS], coef_type biais[NB_BIAIS], image_type image_in[TAB_SIZE], image_type image_out[TAB_SIZE], int base_coeffs, int base_biais, int ncan_in, int ncan_out, int size);

#endif
