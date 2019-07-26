#ifndef TYPES_H
#define TYPES_H

//#include <ac_fixed.h>

// ------------------ INPUT SIZES ------------------

#define IMAGE_WIDTH 24
#define IMAGE_HEIGHT 24

#define NB_COEFFS 27720
#define NB_BIAIS 126

#define TAB_SIZE 36864

// ------------------ CONV PARAMETERS ------------------

// Conv 1
#define NCAN_IN_1 3
#define NCAN_OUT_1 64
#define BASE_COEFFS_1 0
#define BASE_BIAIS_1 0
#define CONV_SIZE_1 24

// Conv 2
#define NCAN_IN_2 64
#define NCAN_OUT_2 32
#define BASE_COEFFS_2 1728 // 9*3*64
#define BASE_BIAIS_2 64
#define CONV_SIZE_2 12

// Conv 3
#define NCAN_IN_3 32
#define NCAN_OUT_3 20
#define BASE_COEFFS_3 20160 //9*64*32 + 1728
#define BASE_BIAIS_3 96
#define CONV_SIZE_3 6

// ------------------ MAXPOOL PARAMETERS ------------------

#define STRIDE 2
#define MP_SIZE 3

// ------------------ RESHAPE PARAMETERS ------------------

#define NCAN_IN_4 20
#define RSP_SIZE 3


// ------------------ PERCEPTRON PARAMETERS ------------------

#define NCAN_IN_5 180
#define NCAN_OUT_5 10
#define BASE_COEFFS_4 25920 //20160 + 9*32*20
#define BASE_BIAIS_4 116

// ------------------ DATA TYPES ------------------
#define DATA_WIDTH 16
#define DATA_FP_LOC 5

#define COEFF_WIDTH 16
#define COEFF_FP_LOC 5

#define SIGNED true
#define UNSIGNED false

// typedef ac_fixed<DATA_WIDTH,DATA_FP_LOC,SIGNED,AC_RND_INF,AC_SAT> image_type ;

// typedef ac_fixed<COEFF_WIDTH,COEFF_FP_LOC,SIGNED,AC_RND_INF,AC_SAT> coef_type ;

// typedef ac_fixed<4,4,UNSIGNED,AC_RND_INF,AC_SAT> led_type;


typedef float image_type ;

typedef float coef_type ;

typedef float led_type;

#endif
