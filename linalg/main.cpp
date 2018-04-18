#include "matrix.hpp"

int main(){
	mat_cont mat1, mat2;
	mat1.set_dim(25);
	mat2.set_dim(25);
	mat1.load_seq();
	mat2.load_seq();
	double sum = mat1.dot(mat2);
	double sum2 = mat1.dot_single_thread(mat2);	
	printf("threads : %lf, no threads : %lf\n",sum,sum2);
	return 0;


}
