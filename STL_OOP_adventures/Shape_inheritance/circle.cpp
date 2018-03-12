#include "Shape.hpp"

Circle::Circle(){
this->radius = 0.0;
}


Circle::Circle(double radius, int id){
	this->id = id;
	this->radius = radius;
}


void Circle::display(void)const{
	double area = get_area();
	printf("radius : %lf, area : %lf, id : %d\n",radius, area, id);
	return;
}


double Circle::get_area(void)const{
	return radius * radius * pi;
}


void Circle::get_dim_attr(attr_circ*& cont)const{
	cont->radius = this->radius;
	return;
}


Circle::~Circle(){}
