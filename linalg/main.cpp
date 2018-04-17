#include "matrix.hpp"

int main(){
	mat_cont mat;
	mat.set_dim(25);
	mat.load_seq();
	mat.display();
	printf ("\n\n %lf ",mat[24][2]);
	return 0;
}
