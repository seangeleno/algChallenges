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
	if (str > this->family)
int8_t HashNode::comp(const string str) const{	//note lack of override keyword. only needs to be in prototype
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
	for( auto iter = this->data.begin(); iter!=this->data.end(); ++iter){ //auto is useful here.
		// we know it will be an iterator, and just treat it as such.  Without auto, this declaration would be
		//too wordy to be usefully readable
		cout << "GENUS " << iter->first << " contains " << endl;

		auto local_vec_size = iter->second.size();  //get size of respective vector
		vector<uint32_t> local_vec = iter->second; //get vector from iterator loc
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
		this->data[str].push_back( value ); //creates new key and pushes value in
		return 2;
	}
	else{
		this->data[str].push_back( value ); //st is used to determine existence of key
		//doesnt need to be used for insertion otherwise with this implementation of unordered_map
		return 1;
	}
}
vector<uint32_t>
HashNode::retrieve(const string str) const
{
	

	vector<uint32_t> outlist = this->data.find(str)->second;

	return outlist;
}





unordered_map<string, vector<uint32_t> >  //note return type.
HashNode::retrieve_map(void) const
{
	return this->data;
}

HashNode::~HashNode(void){
	if (this->paths)
		delete paths;
}
