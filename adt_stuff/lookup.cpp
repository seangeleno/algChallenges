#include "lookup.hpp"
lookup::lookup(void) : __sz(0), __tbl(NULL){}

lookup::lookup(int size) : __sz(size), __tbl(new node*[size]){
	memset(__tbl, 0, sizeof(node*)*__sz);
}









int lookup::hash(const string name)const{
	char* cstr = name.get_str();
	int len = strlen(cstr);
	int sum = 0;
	for(int i =0; i < len; ++i)
		sum+=cstr[i];
	return sum;
}


void lookup::add_to(const int nargs, const string name, p_tuple * params){
	int val = hash(name);
	node * curr = __tbl[val % __sz];
	node * lag;
	if (!curr){
		__tbl[val % __sz] = new node(nargs, name, params);
		return;
	}

	while( (curr->next)&&(curr->name != name)){
		lag = curr;
		curr = curr->next;
	}
	if (!curr)
		lag->next = new node(nargs, name, params);
	return;
}	

/*int lookup::insert(const string tble_in_){
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
}*/


/*void lookup::display(void)const{
	for (int i = 0; i < __sz; ++i){
		node * curr = __tbl[i];
		while(curr){
			curr->dat.display();
			curr = curr->next;
		}

	}
	return;
}
*/

table lookup::retrieve(const string name) const{
	int sum = hash(name);
	node * loc = __tbl[sum%__sz];
	while( loc ){
		if (loc->name != name )
			loc = loc->next;
		else break;
	}


	if (!loc) return NULL;
	return loc->d;
}

	
/*int lookup::remove(const string& desig){

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

*/
lookup::~lookup(){
	for (int i = 0; i < __sz; ++i){
		node * curr = __tbl[i];
		node * del_;
		while(curr){
			del_ = curr;
			curr = curr->next;
			delete del_;
		}
	}
	delete[] __tbl;
}


