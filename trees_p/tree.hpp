#pragma once

#include <stdio.h>
#include <cstdlib>


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
	void pre(node*&,int, int, char*&,const int, const int, const int, const int);
	void in_(node*&,int);
	void post(node*&);
	int destr_tree(node*&);
	int get_num_children(node*,int&,int);
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

/*
struct node_23{
	node_23* child[3];
	int dat;
	node_23() : dat(0){
		memset(child, NULL, 3*sizeof(node_23 *));
	}
	node_23(int d){
		dat = d;
		memset(child, NULL, 3*sizeof(node_23*));
	}
	~node_23();
};

class tree_23{
private:
	node_23 * root;
private:
};


*/
