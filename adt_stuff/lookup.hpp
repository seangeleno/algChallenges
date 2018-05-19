#pragma once

#include "string.hpp"
#include "table.hpp"
#include <iostream>
class node{
public:
	node* next;
	string name;
	table d;
	node(void) : next(NULL), name(), d(NULL){}
	node(int nargs, string name, p_tuple * p_bus){
		this->name = name;
		d = *(new table(nargs, name, p_bus));
		next = NULL;
	}
};














class lookup{
private:
	node** __tbl;
	int __sz;
public:
	lookup();
	lookup(int);
	~lookup();
	void add_to(const int, const string, p_tuple * );
	int hash(const string)const;
	table retrieve(const string)const;
};

