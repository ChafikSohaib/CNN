#include "lowrisc_memory_map.h"
#include "mini-printf.h"

#include <stdio.h>
#include <stdint.h>

#include "types.h"

#include "coeffs_cifar.h"
#include "biases_cifar.h"


#include "testimage.h"

static led_type cifar_class[1];

char names[10][15] = {
	"airplane", "automobile", "bird", "cat", "deer", "dog", "frog", "horse", "ship", "truck"
};


void argmax(image_type image_in[TAB_SIZE], led_type cifar_class[1]) {
	int indice_max = 0;
	for (int i = 1; i< NCAN_OUT_5; i++){
		if (image_in[i] > image_in[indice_max]) indice_max = i;		
	}
	cifar_class[0] = indice_max;
}


void convolution(coef_type matrice[9], image_type image_in[TAB_SIZE], image_type image_out[TAB_SIZE], int size, int base_in, int base_out) { 
    
		image_type acc;
	  for(int j = 0; j<size; j++) {
			for(int i = 0; i<size; i++) {
				acc = 0;
		    for(int n = 0; n<3; n++){
					for(int m = 0; m<3; m++){
						if( ((j-1+n) >= 0) && ((i-1+m)>=0) && ((j-1+n) <= size-1) && ((i-1+m) <= size-1) ) {
							acc += matrice[ n*3+ m ] * (image_in[base_in + (j-1+n)*size + (i-1+m)]);		 				
						}
					}
				}
				image_out[ base_out + j*size + i] += acc;  
			}
		}
}

void multi_convolution(coef_type coeffs[NB_COEFFS], coef_type biais[NB_BIAIS], image_type image_in[TAB_SIZE], image_type image_out[TAB_SIZE], int base_coeffs, int base_biais, int ncan_in, int ncan_out, int size) { 
	coef_type matrice[9];
	for(int i = 0; i < ncan_out; i++) {
		for(int j = 0; j < ncan_in; j++) {
		  for(int k = 0; k < 9; k++) {
				matrice[k] = coeffs[base_coeffs + k*ncan_in*ncan_out + i + ncan_out*j]; 
			}
			convolution(matrice, image_in, image_out, size, size*size*j, size*size*i); 			
		}
		for(int l= 0; l< size*size; l++) {
			image_out[size*size*i + l] += biais[base_biais + i];
			if (image_out[size*size*i + l] < 0) {
				image_out[size*size*i + l] = 0;
			}
		}
	}
  printf("convolution done \n");
	
}


void flush_mem(image_type tab[TAB_SIZE]) {
	 for(int i = 0; i< TAB_SIZE; i++) {
		tab[i] = 0;
	} 
}



void maxpool(image_type image_in[TAB_SIZE], image_type image_out[TAB_SIZE], int size, int base_in, int base_out){
	int new_size = size/STRIDE;
	image_type max = 0;
	for(int j = 0; j < new_size; j++) {
		for(int i = 0; i < new_size; i++) {
			max = 0;
			for(int m = 0; m < MP_SIZE; m++ ) {
				for(int n =0; n < MP_SIZE; n++) {
					if( ((i*STRIDE + n) < size) && ((j*STRIDE + m) < size) ) {
						if (image_in[base_in + i*STRIDE + j*STRIDE*size + m*size + n] > max) {
							max = image_in[base_in + i*STRIDE + j*STRIDE*size + m*size + n];
						}
					}
				}
			}
			image_out[base_out + j*new_size + i] = max;
		}
	}
}

void multi_maxpool(image_type image_in[TAB_SIZE], image_type image_out[TAB_SIZE], int ncan, int size){
	int new_size = size/STRIDE;
	for(int i = 0; i<ncan; i++) {
		maxpool(image_in, image_out, size, i*size*size, i*new_size*new_size);
	}
  printf("maxpool done \n");
}


void perceptron(coef_type coeffs[NB_COEFFS], coef_type biais[NB_BIAIS], image_type image_in[TAB_SIZE], image_type image_out[TAB_SIZE]) {
	image_type acc;
	for(int i = 0; i < NCAN_OUT_5; i++) {
		acc = 0;
		for(int j = 0; j < NCAN_IN_5; j++) {
			acc += image_in[j]*coeffs[BASE_COEFFS_4 + i + j*NCAN_OUT_5];
		}
		image_out[i] = acc + biais[BASE_BIAIS_4 + i];
	}
  printf("perceptron done \n");
}



void reshape(image_type image_in[TAB_SIZE], image_type image_out[TAB_SIZE]) {
	for(int i = 0; i < NCAN_IN_4; i++) {
		for(int j = 0; j < RSP_SIZE*RSP_SIZE; j++) {
			image_out[i+j*NCAN_IN_4]=image_in[i*RSP_SIZE*RSP_SIZE+j];
		}
	}
	printf("reshape done \n");
}


image_type image_1[TAB_SIZE]; 
image_type image_2[TAB_SIZE];


void top()
{	



	printf(">>>>> CNN starts >>>>> \n");
	
 	flush_mem(image_1);
 	flush_mem(image_2);
	

// FILL IMAGE
	printf("// FILL IMAGE \n");
	for(int i = 0; i< IMAGE_WIDTH*IMAGE_HEIGHT*3; i++) {
		image_1[i] = image_test[i];
	}


// STEP 1
	printf("// STEP 1 - start \n");

	multi_convolution(tab_coeffs, tab_biais, image_1, image_2, BASE_COEFFS_1, BASE_BIAIS_1, NCAN_IN_1, NCAN_OUT_1, CONV_SIZE_1);
	flush_mem(image_1);
	multi_maxpool(image_2, image_1, NCAN_OUT_1, CONV_SIZE_1);
	flush_mem(image_2);

// STEP 2
	printf("// STEP 2 - start \n");

	multi_convolution(tab_coeffs, tab_biais, image_1, image_2, BASE_COEFFS_2, BASE_BIAIS_2, NCAN_IN_2, NCAN_OUT_2, CONV_SIZE_2);
	flush_mem(image_1);
	multi_maxpool(image_2, image_1, NCAN_OUT_2, CONV_SIZE_2);
	flush_mem(image_2);

// STEP 3
	printf("// STEP 3 - start \n");
	multi_convolution(tab_coeffs, tab_biais, image_1, image_2, BASE_COEFFS_3, BASE_BIAIS_3, NCAN_IN_3, NCAN_OUT_3, CONV_SIZE_3);
	flush_mem(image_1);
	multi_maxpool(image_2, image_1, NCAN_OUT_3, CONV_SIZE_3);
	flush_mem(image_2);

	printf("// STEP 4 \n");

// RESHAPE
	reshape(image_1, image_2);

// PERCEPTRON
	flush_mem(image_1);
	perceptron(tab_coeffs, tab_biais, image_2, image_1);
	
// ARGMAX
	argmax(image_1, cifar_class);

	printf(">>>>> CNN done >>>>> \n");

}


int main() {
  
	top();	
	printf("Classified as %s \n", names[(int)cifar_class[0]]);
    
	return 0;

}
