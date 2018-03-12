#include "Shape.hpp"

Rectangle::Rectangle(void){}


Rectangle::Rectangle(double length, double width, int id){
	this->id = id;
	this->length = length;
	this->width = width;
}


void Rectangle::display(void)const{
	double area = length * width;
	printf("length: %lf, width: %lf, area: %lf id: %d\n", length, width, area, id);

	return;
}


double Rectangle::get_area(void)const{
	return length * width;
}


Rectangle::~Rectangle(void){}
