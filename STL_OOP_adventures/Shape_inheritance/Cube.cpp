#include "Shape.hpp"

Cube::Cube(void){
	width = length = height = 0.0;
}
Cube::Cube(double in_len, int id){
	this->id = id;
	width = length = height = in_len;
}




void Cube::get_dim_attr(attr_box *& cont)const {
	cont->length = this->length;
	cont->width = this->width;
	cont->height = this->height;
	return;
}




double Cube::get_volume(void)const{
	double volume = pow(width,3);
	return volume;
}

void Cube::display(void)const{
	printf("%lf %lf %lf id : %d\n", length, width, height, id);
	return;
}
Cube::~Cube(){}
