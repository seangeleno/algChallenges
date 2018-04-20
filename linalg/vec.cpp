#include "matrix.hpp"

vec::vec() : dimx(0), mat(NULL){}

vec::vec(const int els){
	mat = new double[els];
	memset(mat, 0.0, sizeof(double)*els);
}


void vec::linspace(double x, double y, const int num){
	double incr_ = ((double)y-x)/(double)num;
	
	if (mat)
		delete[] mat;
	dimx = num;
	mat = new double[num];
	for (int i = 0; i < num; ++i)
		mat[i] = x + i*incr_;
	return;
}


void vec::display(void)const{
	printf("[");
	for (int i = 0; i < dimx; ++i){
		printf("%.2f", mat[i]);
		if (i != dimx-1)
			printf(", ");
	}
	printf("]\n");
}

vec::~vec(){
	if (mat)
		delete[] mat;
}
