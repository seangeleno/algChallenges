#include "Node.hpp"

Node::Node(){
	this->next[0] = (Node*)0;
	this->next[1] = (Node*)0;
	this->paths=NULL;
}


int8_t Node::insert_path(Node*& rx){
	if (!this->paths)
		this->paths = new vector<Node*>;


	this->paths->push_back(rx);
	return 1;
}


void Node::disp_short(void) const{
	return;
}
Node::~Node(){
	if (this->paths){


		cout<<2<<endl;
	}





}