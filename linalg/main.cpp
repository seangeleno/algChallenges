#include "matrix.hpp"

int main(){
	box mat1; vec mat2;
	mat1.set_dim(7);
	mat1.xf();
	mat2.linspace(1.0, 7.0,50);
	mat1.load_seq();
	mat1.display();
	mat2.display();
	return 0;


}
