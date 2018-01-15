#include "Node.hpp"

using namespace std;
StringNode::StringNode(void){
	this->prev=NULL;
	this->paths = NULL;
}


StringNode::StringNode(const string str){
	this->data = str;
	this->paths = NULL;
}


StringNode::StringNode(const string str, const Node *& parent){
	//this->prev = parent;
	this->data = str;
	this->paths = NULL;

}


int8_t StringNode::insert(const string str){
	//TODO make more robust to changes, handle overwriting
	if (this->data.length() <=1)
		this->data = str;
	return 1;
}
void StringNode::disp_short(void) const{
	cout << "\t" << this->data << endl;
}
string StringNode::retrieve(const string str) const {
	return this->data;
}
int8_t StringNode::comp(const string str) const{
	if ( this->data > str)
		return 1;
	else if ( this->data == str)
		return 0;
	return -1;	
}

void StringNode::display (void)  const{
	cout << "PHYLUM " << this->data << endl;
	if (this->paths){
		cout << "PHYLUM " << this->data << " contains connections directly to" <<endl;
		for (auto i = 0; i < this->paths->size(); ++i){
			this->paths->at(i)->disp_short();
		}
	}
	return;
}


StringNode::~StringNode(){
	if (this->paths)
		delete paths;

}




