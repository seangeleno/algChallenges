#ifndef SHAPE
#define SHAPE

#define pi 3.1415926535
#include <iostream>

#include <stdlib.h>
#include <math.h>

class attr{
public:
	int baba;
	attr(void){}
	~attr(void){}
};

class Shape{
protected:
	int id;
	int dimension;
public:
	Shape();
	~Shape();
	virtual int get_dimension()const=0;
	virtual int get_id()const;
	virtual void display(void)const=0;
};



class TwoDShape : public Shape{
public:
	TwoDShape();
	~TwoDShape();
	virtual double get_area(void)const=0;
	int get_dimension(void)const override;
};


class ThreeDShape : public Shape{
public:
	ThreeDShape();
	~ThreeDShape();	
	virtual double get_volume(void)const=0;
	int get_dimension(void)const override;
};




class attr_box : public attr{
public:
	double length;
	double width;
	double height;
};




class attr_circ : public attr{
public:
	double radius;
};


class Circle: public TwoDShape{
private:
	double radius;
public:
	Circle();
	Circle(double, int);
	~Circle(void);
	
	double get_area(void)const override;
	void get_dim_attr(attr_circ*&)const;
	void display(void)const override;
};





class Box : public ThreeDShape{
protected:
	double length;
	double width;
	double height;
public:
	Box();
	Box(double,double,double, int);
	~Box();
	
	void display(void)const override;
	double get_volume(void) const override;
	void get_dim_attr(attr_box*&) const;
};



class attr_sph : public attr{
public:
	double radius;
};

class Sphere : public ThreeDShape{
private:
	double radius;
public:
	Sphere();
	Sphere(double,int);

	~Sphere();

	double get_volume(void) const override;
	void get_dim_attr(attr_sph*&) const;
	void display(void)const override;
};







class attr_rect : public attr{
public:
	double length;
	double width;
};


class Rectangle : public TwoDShape{
protected:
	double length;
	double width;



public:
	 Rectangle();
	 Rectangle(double, double, int);
	~Rectangle();	
	double get_area(void) const override;
	void get_dim_attr(attr_box*&) const;
	void display(void)const override;
};

class Square : public Rectangle{
public:
	Square(void);
	Square(double,int);
	~Square(void);

	double get_area(void) const override;
	void get_dim_attr(attr_rect*&) const;
	void display(void)const override;
};
class Cube : public Box{
public:
	Cube(void);
	Cube(double,int);
	~Cube(void);

	double get_volume(void) const override;
	void get_dim_attr(attr_box*&) const;
	


	void display(void)const override;
};

#endif
