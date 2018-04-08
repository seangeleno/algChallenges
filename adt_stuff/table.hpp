#pragma once

#include "string.hpp"
#include "query.hpp"
#include <iostream>
struct node{
	node* next;
	query dat;
};














class table{
private:
	node** __tbl;
	int __sz;
public:
	table();
	~table();
	int insert(const query&);
	int remove(const string&);
	query retrieve(const string&)const;
	void display(void)const;
};

