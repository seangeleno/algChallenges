#pragma once

#include "string.hpp"
#include <iostream>
struct node{
	node* next;
	string dat;
};














class table{
private:
	node** __tbl;
	int __sz;
public:
	table();
	~table();
	int insert(const string&);
	void display(void)const;
};

