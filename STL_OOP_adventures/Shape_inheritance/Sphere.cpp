#include "Shape.hpp"

Sphere::Sphere(void){	
	this->radius=0.0;
};


Sphere::Sphere(double radius_in, int id){
	this->id = id;
	this->radius = radius_in;
}


void Sphere::get_dim_attr(attr_sph *& cont) const{
	cont->radius = this->radius;
	return;
}


double Sphere::get_volume(void) const{
	double volume = pow(3,radius) * pi * 4.0/3.0;
	return volume;
}


void Sphere::display(void) const{
	double volume = get_volume();
	printf("radius : %lf, volume : %lf, id : %d\n",radius,volume,id);
	return;
}


Sphere::~Sphere(){}
