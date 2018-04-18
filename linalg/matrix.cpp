#include "matrix.hpp"

matrix::matrix(void) : dimx(0), dimy(0), mat(NULL){}

matrix::matrix(const int x, const int y)  : dimx(x), dimy(y), mat(new double[x*y]){}


void matrix::load_seq(void){
	for (int i = 0; i < dimx; ++i){
		for (int j = 0; j < dimy; ++j){
			mat[i*dimx+j] = i*dimx + j;
		}
	}

	return;
}




void matrix::display(void) const { 
	printf("[");
	for (int i = 0; i < dimx; ++i){
		for (int j = 0; j < dimy; ++j){
			printf("[%lf]",mat[i * dimx + j]);
			if ( j != dimy-1)
				printf(", ");
			
		}
		printf("]\n");
		if (i != dimx-1)
			printf("[");
	}
	return;
}

void matrix::set_dim(const int x, const int y){
	dimx = x; 
	dimy = y;	
	if (mat)
		delete[] mat;
	mat = new double[x*y];
}
matrix::~matrix(){
	if (mat)
		delete[] mat;
}

