#pragma once

#include "string.hpp"
#include "query.hpp"
#include <iostream>
struct node{
	node* next;
	entry __ntr;
};














class lookup{
private:
	node** __tbl;
	int __sz;
public:
	lookup();
	~lookup();
	int insert(const query&);
	int remove(const string&);
	query retrieve(const string&)const;
	void display(void)const;
};

