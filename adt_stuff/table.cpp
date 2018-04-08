#include "table.hpp"
table::table(void){
	__sz = 53;
	__tbl = new node*[__sz];
	memset(__tbl,0,__sz*sizeof(node*));

}












int table::insert(const string& in_){
	int sum = 0;
	for (int i = 0; i < in_.size(); ++i)
		sum+=in_[i];	

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
			std::cout << curr->dat << std::endl;
			curr = curr->next;
		}
	}
	return;
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


