#include "Tree.hpp"













Tree::Tree(){
	this->head=NULL;
}


Tree::Tree(const string str ){
	this->head= new StringNode(str);
}

Tree::Tree(string fam_setter, string key, 
uint32_t datum)
{
	this->head = new HashNode(fam_setter,key,datum);
}
int8_t Tree::insert( const string str ){
	//if head not defined, head node is a StringNode. pass forward to enter
	//recursive call
	if (!this->head){
		this->head = new StringNode(str);
		return 5;
	}
	Node * current = this->head;
	Node * parent;
	bool l_g;
	while( current ){
		parent = current;
		if ( current->comp(str) < 0){
			l_g = 0;
			current = current->next[0];
		}	else {
			l_g = 1;	
			current = current->next[1];
		}
	}
	if (!l_g)
		parent->next[0] = new StringNode(str);
	else
		parent->next[1] = new StringNode(str);
	return 1;
}


int8_t Tree::insert( string fam_checker, string key_in,
 uint32_t datum)
{
	Node * current = this->head;
	Node * parent;
	bool l_g;
	while(current){
		int8_t comparison_output = current->comp(fam_checker);
		if (comparison_output == 0){
			return dynamic_cast<HashNode*>(current)->insert(key_in, datum);
		}
		parent = current;
		if (comparison_output < -1){
			current = current->next[0];
			l_g = 0;
		}
		else{
			current = current->next[1];
			l_g = 1;
		}

	}
	if (!l_g)
		parent->next[0] = new HashNode(fam_checker, key_in, datum);
	else 
		parent->next[1] = new HashNode(fam_checker,key_in,datum);
	return 1;
}

int8_t Tree::insert_path( const string rx_str, const string tx_str){
	Node * current = this->head;
	return insert_path(rx_str, tx_str, current);
}
int8_t Tree::insert_path( const string rx_str, const string tx_str, Node * current ){
	//reach point to insert path back to whatever node we want coneciton to
	//traverse to node of interest recursively
	if (!current)
		return -1;

	//check for matching value to confirm insertion. else traverse left or right
	int8_t comparison_output = current->comp(rx_str); 
	if (comparison_output == 0){
		if (tx_str < rx_str)
			return insert_path(tx_str, current, this->head);
		return insert_path(tx_str, current, this->head);
	}

	else if (comparison_output < 0)
		return insert_path(rx_str, tx_str, current->next[0]);
	else 
		return insert_path(rx_str, tx_str, current->next[1]);
}

int8_t Tree::insert_path( const string str, Node*& rx, Node * current ){
	//introduce loops to loosely defined "tree" data structure 
	//handles process of insertion
	if (!current)
		return -1;


	if (current->comp(str) == 0){
		current->insert_path(rx);
		return 1;
	}
	else{
		if (current->comp(str) < 0)
			return insert_path(str, rx, current->next[0]);
		return insert_path(str, rx, current->next[1]);
	}
}



vector<uint32_t>
Tree::retrieve(const string family_id, const string genus_id )const {
	Node * current = this->head;
	while(current){
		int8_t comparison_output = current->comp(family_id);
		if (comparison_output == 0)
			return dynamic_cast<HashNode*>(current)->retrieve(genus_id);
		else if (comparison_output < 0)
			current = current->next[0];
		else
			current = current->next[1];
	}
}
unordered_map<string, vector<uint32_t> >
Tree::retrieve_map(const string fam) const{
	Node * current = this->head;
	while(current){
		int8_t comparison_output = current->comp(fam);
		if (comparison_output == 0)
			return dynamic_cast<HashNode*>(current)->retrieve_map();
		else if (comparison_output < 0)
			current = current->next[0];
		else if (comparison_output < 0)	
			current = current->next[1];
	}

}

void Tree::display_one( const string str, Node * current ) const {
	//traverse to node to display recursively
	if (!current)
		return;
	int8_t comparison_output = current->comp(str);
	if (comparison_output == 0){
		current->display();
	}
	else if (comparison_output > 0)
		return display_one( str, current->next[0]);
	return display_one(str, current->next[1]);

}

void Tree::display_one( string str ) const{
	//handles entering tree to display the requested node
	Node * current = this->head;
	return display_one(str, current);
}





void Tree::display_all( void ) const {
	// handles entry into tree
	Node * current = this->head;
	return display_all(current);
}

void Tree::display_all( Node* current ) const {
	// recursively traverse in order all nodes and
	// display respective contents
	if (!current) 
		return;
	display_all( current->next[0] );
	current->display();
	display_all( current->next[1]);
	return;
}






int8_t Tree::EOU_del( Node *& current ){
	// post order traverse and delete necessary
	// allocated path vectors

	if (!current)
		return 0;
	EOU_del( current->next[0]);
	EOU_del( current->next[1]);
	delete current;
	return 1;



}

Tree::~Tree(){
	EOU_del(this->head);
}	








/*
RECURSIVE IMPLEMENTATIONS LEFT IN SO RECRUITERS KNO I GOT THE SKILLZ
int8_t tree::insert( const String str ){
	//if head not defined, head node is a StringNode. pass forward to enter
	//recursive call
	if (!this->head){
		this->head = new StringNode(str);
		return 5;
	}
	return insert(str, this->head);
}




int8_t tree::insert_path( const String str, Node * current ){
	//reach point to begin loop back to
	if (!current)
		return -1;
	int8_t comparison_output = current->comp(str)
	if (comparison_output == 0){
		int depth = 0;
		int current_depth = 0; 
		return insert_path();
	}
	else if (comparison_output < 0)
		return insert_path()
	else if (comparison_output > 0)
		return insert_path()
	else return -2;
}

int8_t tree::insert_path( const String str, const Node*& rx, Node * current, int & depth, int & current_depth){
	//introduce loops to loosely defined "tree" data structure 
	if (!current)
		return -1;
	++current_depth;
	if (depth == current_depth){
		current->next.push_back(rx);
		return 1;
	}
	else{
		//TODO expand next array to vector of node pointers
		if (current->comp(str) < 0)
			return insert_path(str, rx, current->next[0], depth, current_depth);
		return insert_path(str, rx, current->next[1], depth, current_depth);
	}
}

int8_t tree::insert( const String str, StringNode*& current){
	//case without previous point. StringNode
	if (!current){
		current = new StringNode(str);
		return 1;
	}
	if (current->comp(str) < 0)
		return insert( str, current->next[0], current);
	return insert( str, current->next[1], current);
}



int8_t tree::insert( const String str, StringNode *& current, const Node*& prev ){
	// case including previous pointer for StringNode
	if (!current){
		current = new StringNode(str, prev);
		return 1;
	}
	if (current->comp(str) < 0)
		return insert( str, current->next[0], current);
	return insert( str, current->next[1], current);
}



int8_t tree::insert( const String str, const uint32_t data ){
	// if head not defined, head is HashNode. Otherwise pass
	// values forward for insertion`
	if (!this->head){
		this->head = new HashNode(str, data);
		return 5;
	}
	return insert( str, data, this->head );
}


int8_t tree::insert( const String str, const uint32_t data, HashNode *& current ){


	//HashNode insertion without previous node
	if (!current){
		current = new HashNode(str, data);
		return 1;
	}
	if (current->comp(str) < 0)
		return insert( str, data, current->next[0], current );
	return insert( str, data, current->[1], current);

}


int8_t tree::insert( const String str, const uint32_t data, HashNode *& current,  const Node *& prev ){
	//HashNode insertion with previous node
	if (!current){
		current = new HashNode(str, data, prev);
		return 1;
	}
	else if (current->comp(value) < 0)
		return insert(value, current->next[0], current);
	else return insert(value, current->next[1], current);
}

*/

