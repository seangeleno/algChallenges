//This Node extension handles c++ strings. These allow under-the-hood handling of dynamic string operations
//This means you do not have to worry about reallocation; the stl::string handles it for you.  concatenation and 
//copying are seemingly robust enough that they become a programmatic afterthought to the user.  This streamlines
//string heavy dev.  It is obviously a cstring underneath the hood, and as such allows conversions between forms. 
//Look to main.cpp for reading in std::strings properly 

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
	if ( str > this->data)
		return 1;
	else if ( this->data == str)
		return 0;
	return -1;	
}

void StringNode::display (void)  const{
	cout << "PHYLUM " << this->data << endl;
	if (this->paths){
		cout << "PHYLUM " << this->data << " contains connections directly to" <<endl;
		//auto is a keyword that allows the compiler to decide what best fits the variables data type.
		//useful for streamlining, but really annoying when used constantly.  Only use when the data type and usage
		//are obvious. in this case, it is a primitive (integer) to iterate through the vector
		for (auto i = 0; i < this->paths->size(); ++i){
			this->paths->at(i)->disp_short(); //at is a function that corresponds to indexing
		}
	}
	return;
}


StringNode::~StringNode(){
//All nodes have an std::vector that allows for dynamic upsizing depending
//on use of the structure. Here, paths is a vector of Node pointers. This allows 
//generalized interaction with other classes dervied from Node abstract class. 
	
//Connects with them across the tree for usage intense demands to cut traversal time.
	if (this->paths)
		delete paths;

}




