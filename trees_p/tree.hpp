#pragma once

#include <stdio.h>
#include <stdlib.h>


struct node{
	node* l, *r;
	int dat;


	node() : dat(0), l(NULL),r(NULL){}
	node(int d){
		dat = d;
		l = r = NULL;
	}

	~node(){
	}
};

class tree{
private:
	node* root;


private:
	int insert(node*&,const int);
	int remove(node*&,const int);
	int seek_ios(node*,node*&);
	int insert(node*&, node*&);	
	void pre(node*&);
	void in_(node*&);
	void post(node*&);
	int destr_tree(node*&);
public:
	tree();
	tree(const int, const int);
	~tree();
	int  set_head(const int);
	int  insert(const int);

	int  remove(const int);
	void display_pre(void);
	void display_in(void);
	void display_post(void);





};
