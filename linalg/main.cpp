#include "matrix.hpp"

int main(){
	box mat1; matrix mat2;
	mat1.set_dim(5);
	mat2.set_dim(5,2);
	mat1.load_seq();
	mat2.load_seq();
	mat1.display();
	mat2.display();
	return 0;


}
