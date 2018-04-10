#ifndef LLL_HEAD_
#define LLL_HEAD_

#include <cstdio>
#include <cstdlib>

#include "Node.hpp"
class LLL{
private:
	int len;
	Node * head, * tail;

	int remove_f_e(Node *&, int);
	int remove_at_r(Node*&, int,const int);
	int remove_fe_fast(Node *&, Node*&, const int, int&);
public:
	LLL();
	LLL(int);
	LLL(int,int);
	~LLL();


	void insert(const int);
	void append(const int);
	int remove_all(const int);
	int remove_at(const int);
	int remove_at_r(const int);
	int remove_from_end(int);
	int remove_fe_fast(const int);
	void display(void)const;	
	
};

#endif
