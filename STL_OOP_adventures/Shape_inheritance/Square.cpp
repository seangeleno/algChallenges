#include "Shape.hpp"

Square::Square(){
	length = width = 0.0;
}


Square::Square(double len, int id){
	this->id = id;
	length = width = len;
}


double Square::get_area(void) const{
	return length * width;

}


void Square::display(void) const{
	double area = this->length * this->width;
	printf("length: %lf width: %lf, area: %lf id: %d\n",
		this->length, this->width, area, this->id);
	return;
}


Square::~Square(){}
