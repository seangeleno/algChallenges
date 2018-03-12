#include "Shape.hpp"

TwoDShape::TwoDShape(void){
	this->dimension = 2;
}

int TwoDShape::get_dimension(void)const{
	return this->dimension;
}

TwoDShape::~TwoDShape(){}
