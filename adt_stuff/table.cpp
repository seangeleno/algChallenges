#include "table.hpp"
table::table(void){
	__sz = 2;
	__tbl = new node*[__sz];
	memset(__tbl,0,__sz*sizeof(node*));

}












int table::insert(const query& in_){
	string str = in_.get_name();
	int sum = 0;
	for (int i = 0; i < str.size(); ++i)
		sum+=str[i];	

	node* loc = __tbl[sum%__sz];
	if (!loc){
		loc = new node;
		loc->dat = in_;
		loc->next = NULL;
		__tbl[sum%__sz] = loc;
		return 1;
	}

	while(loc->next)
		loc = loc->next;
	node* temp = new node;
	temp->dat = in_;
	temp->next = NULL;
	loc->next = temp;
	return 1;
}


void table::display(void)const{
	for (int i = 0; i < __sz; ++i){
		node * curr = __tbl[i];
		while(curr){
			curr->dat.display();
			curr = curr->next;
		}

	}
	return;
}


query table::retrieve(const string& name) const{
	int sum = 0;
	int size = name.size();
	for (int i = 0; i < size; ++i)
		sum += name[i];
	node * loc = __tbl[sum%__sz];
	while( loc ){
		if (loc->dat.get_name() != name )
			loc = loc->next;
		else break;
	}


	if (!loc) return NULL;
	query query_out = loc->dat;
	return query_out;
}

	
int table::remove(const string& desig){

	int sum = 0;
	int size = desig.size();

	for(int i = 0; i < size; ++i)
		sum+=desig[i];

	node * loc = __tbl[sum % __sz];
	while(loc){
		if (loc->dat.get_name()!=desig)
			loc = loc->next;
		else{
			cout << "found" << std::endl;
			break;
		}
	}

	return 1;
}


table::~table(){
	for (int i = 0; i < __sz; ++i){
		node * curr = __tbl[i];
		node * del_;
		while(curr){
			del_ = curr;
			curr = curr->next;
			delete del_;
		}
	}
}


