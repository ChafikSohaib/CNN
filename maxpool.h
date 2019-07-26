#ifndef MAXPOOL_H
#define MAXPOOL_H


#include "types.h"

void maxpool(image_type image_in[TAB_SIZE], image_type image_out[TAB_SIZE], int size, int base_in, int base_out);
void multi_maxpool(image_type image_in[TAB_SIZE], image_type image_out[TAB_SIZE], int ncan, int size);

#endif
