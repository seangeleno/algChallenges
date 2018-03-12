#include "Shape.hpp"

ThreeDShape::ThreeDShape(){
	this->dimension=3;
}

int ThreeDShape::get_dimension(void) const{
	return dimension;
}

ThreeDShape::~ThreeDShape(){}
