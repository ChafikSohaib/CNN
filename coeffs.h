#ifndef FILTER_H
#define FILTER_H

#include "types.h"

#define FILTER_SIZE 9

/*
// filtre unitaire - validé sur FPGA
static coef_type coeffs[FILTER_SIZE] = {
0.0, 0.0, 0.0, 
0.0, 1.0, 0.0, 
0.0, 0.0, 0.0
};
*/

/*

// detection de contour version 1 - validé sur FPGA - photo
static coef_type coeffs[FILTER_SIZE] = {
-1.0, -1.0, -1.0,
-1.0, 8.0, -1.0, 
-1.0, -1.0, -1.0
};


// 3d - - validé sur FPGA - photo
static coef_type coeffs[FILTER_SIZE] = {
-1.0, -1.0, 0.0, 
-1.0, 0.0, 1.0, 
0.0, 1.0, 1.0
};



// detection de contour version 2 - validé sur FPGA
static coef_type coeffs[FILTER_SIZE] = {
-1.0, 0.0, 1.0, 
0.0, 0.0, 0.0, 
1.0, 0.0, -1.0
};
*/


// sharpen edges / bords tranchants - validé sur FPGA - photo
static coef_type coeffs[FILTER_SIZE] = {
0.0, -1.0, 0.0, 
-1.0, 5.0, -1.0, 
0.0, -1.0, 0.0
};

#endif
