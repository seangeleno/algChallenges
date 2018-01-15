#include "Node.hpp"

using namespace std;



HashNode::HashNode(){
	this->prev=NULL;
	this->paths=NULL;
}


HashNode::HashNode(string fam_setter){
	this->prev=NULL;
	this->paths = NULL;
	this->family = fam_setter;
}


HashNode::HashNode( string fam_setter,  string str,
uint32_t value) 
{
	this->family = fam_setter;
	this->data[str].push_back(value);
	this->prev=NULL;
	this->paths=NULL;
}










int8_t HashNode::comp(const string str) const{	
	if (this->family > str)
		return 1;
	else if (this->family == str)
		return 0;
	return -1;
}
int8_t HashNode::insert( string str){
	this->family = str;
	return 1;
}


void HashNode::display(void)const{
	cout << "FAMILY " << this->family << endl;
	for( auto iter = this->data.begin(); iter!=this->data.end(); ++iter){
		cout << "GENUS " << iter->first << " contains " << endl;

		auto local_vec_size = iter->second.size();
		vector<uint32_t> local_vec = iter->second;
		for (size_t i = 0;  i < local_vec_size; ++i){
			cout << '\t' << local_vec[i] << endl;
		}	
	}
	if (this->paths){
		cout << "FAMILY " << this->family << " connects directly to  "<<
		"these other families " << endl;
		for (auto i = 0; i < this->paths->size(); ++i)
			this->paths->at(i)->disp_short();
	}
	return;	


}

void HashNode::disp_short(void)const{
	cout << "\t" << this->family << endl;
	return;

}



int8_t HashNode::insert(string str, uint32_t value){
	unordered_map<string, vector<uint32_t> >::
		const_iterator st = this->data.find( str );

	if (st == this->data.end()){
		this->data[str].push_back( value );
		return 2;
	}
	else{
		this->data[str].push_back( value );
		return 1;
	}
}
vector<uint32_t>
HashNode::retrieve(const string str) const
{
	

	vector<uint32_t> outlist = this->data.find(str)->second;

	return outlist;
}





unordered_map<string, vector<uint32_t> > 
HashNode::retrieve_map(void) const
{
	return this->data;
}

HashNode::~HashNode(void){
	if (this->paths)
		delete paths;
}