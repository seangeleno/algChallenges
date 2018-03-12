#include "Shape.hpp"

Box::Box(){
	length=width=height = 0.0;
}

Box::Box(double width, double length, double height, int id){
	this->id = id;
	this->length = length;
	this->width = width;
	this->height = height;

}

void Box::get_dim_attr( attr_box *& cont )const {
	cont->length = this->length;
	cont->width = this->width;
	cont->height = this->height;
	return;
}
void Box::display(void)const{
	double volume = length * width * height;
	printf("length : %lf widthe : %lf height : %lf volume : %lf id : %d \n", length, width, height, volume, id);
	return;
}
double Box::get_volume(void)const{
	double volume = length*width*height;
	return volume;
}

Box::~Box(){}
