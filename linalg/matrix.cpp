#include "matrix.hpp"

mat_cont::mat_cont(void){
	this->dim = 0;
	this->mat = NULL;
}

mat_cont::mat_cont( const int dim){
	this->dim = dim;
	mat = new double[dim*dim];
}


void mat_cont::display(void) const{
	printf("[");
	for (int i = 0; i < dim; ++i){
		for (int j = 0; j < dim; ++j){
			printf("[%d]", (int)mat[i * dim + j]);
			if ( j != dim - 1)
				printf(", ");
		}
		printf("]\n");			
		if (i != dim-1)
			printf("[");
	}
}

mat_cont::~mat_cont(){
	delete[] mat;
}

void mat_cont::load_seq(void){
	for (int i = 0; i < dim; ++i){
		for (int j = 0; j < dim; ++j){
			mat[i * dim + j] = i * dim + j;
		}
	}
}


void mat_cont::set_dim(const int dim){
	this->dim = dim;
	if (mat)
		delete[] mat;
	mat = new double[dim*dim];
}
