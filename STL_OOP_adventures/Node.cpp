#include "Node.hpp"
//This is an abstract class.  Note that the constructor MUST be implemented.  
//It is called during instantiation of derived classes. The rest of the functions are just there
//to give an example of implmentation. The destructor contains a readout in order to verify proper destruction

Node::Node(){
<<<<<<< HEAD
	this->next[0] = (Node*)0;
	this->next[1] = (Node*)0;
=======
	//Leaving left and right pointers inside of an array for ease of extension down the line
	// in dev.
	this->next[0] = NULL;
	this->next[1] = NULL;
>>>>>>> refs/remotes/origin/master
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
