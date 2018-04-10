#include "lll.hpp"


LLL::LLL(void){
	len=0;
	head=tail=NULL;
}

LLL::LLL(int dat){
	len=0;
	insert(dat);
}


LLL::LLL(int size, int max){
	len = 0;
	srand(2);
	for (int i = 0; i < size; ++i){
		int rn_dat = rand()%max;
		insert(rn_dat);
	}
}


void LLL::insert(const int dat){
	if(!head){
		this->head = new Node;
		head->data = dat;
		head->next = NULL;
		tail = head;
		++len;
		return;
	}
	Node * temp = new Node;
	temp->next = head;
	temp->data = dat;
	head = temp;
	++len;
	if (len==2)
		tail = temp->next;
	return;
}


void LLL::append(const int dat){
	if (!tail){
		tail = new Node;
		tail->data = dat;
		tail->next = NULL;
		head = tail;
		++len;
		return;
	}
	tail->next = new Node;

	Node * temp = tail->next;
	temp->next = NULL;
	temp->data = dat;
	++len;
	if (len==2)
		head = tail;
	tail = temp;
	return;
}


int LLL::remove_all(const int dat){
	Node * curr = head;
	int removal_counter = 0;
	while (curr && curr->next){
		if (curr->next->data == dat){
			Node* del = curr->next;
			curr->next = curr->next->next;
			delete del;
			++removal_counter;
		}
		else
			curr = curr->next;
	}
	len-=removal_counter;
	return removal_counter;
}



int LLL::remove_at_r(const int dat){
	int iter = 0;
	return remove_at_r(head,iter, dat);
}


int LLL::remove_at_r(Node*& curr, int iter, const int dat){
	if (!curr)
		return 0;
	if (!(curr->next->next))
		tail = curr;
	if (dat == iter){
		Node * temp = curr->next;
		delete curr;
		curr = temp;
		return 1;
	}
	++iter;
	return remove_at_r(curr->next,iter,dat);
}

int LLL::remove_at(const int dat){
	int iter = 0;
	Node * del, * curr;
	if (dat == 0){
		curr = curr->next;
		delete head;
		head = curr;
		return 1;
	}

	while(curr && curr->next && iter!=(dat-1)){
		curr = curr->next;
		++iter;
	}
	if (curr && curr->next && (dat-1 == iter)){
		if (curr->next == this->tail)
			tail = curr;
		del = curr->next;	
		curr->next=curr->next->next;
		--len;
		delete del;
		return 1;
	}
	return 0;
}
		

int LLL::remove_from_end(int dat){
	--dat;
	return remove_f_e(head,dat);
}




int LLL::remove_f_e(Node *& curr,  int dat){
	if (!curr)
		return 0;
	int sig = remove_f_e(curr->next, dat) + 1;
	if (sig == -1) return -1;
	else if ((dat == len-1) && (sig == dat-1))
		tail = curr;
		
	else if(sig == dat)
	{
		Node * temp = curr->next;
		delete curr;
		curr = temp;
		return -1;
	}
	return sig;
}
/*
int LLL::remove_fe_fast(const int dat){
	Node * fast_ptr = head;
	Node * slow_ptr = head;
	int ctr = 0;
	return remove_fe_fast(slow_ptr, fast_ptr, dat, ctr);



}

int LLL::remove_fe_fast(Node *& slow_ptr, Node*& fast_ptr, const int dat,
	int& ctr)
{
	//lets say a certain company wants you to optimize retrieval in least 
	//operations or something like that. how would you do it or something
	
	//the for loop is used to specify whether or not we are in range of 
	//the list. if we are, we care about these ptrs.b In fact, we can use the 
	//difference between the end and that number to get the position and 
	//optimize more. But this allows us to skip "dat" nodes on our way back

	bool flg = false;
	int sig = 0;
	if (!slow_ptr&&!fast_ptr)
		return 0;
	for (int i = 0; i < dat; ++i){
		if (!fast_ptr->next){
			sig = remove_fe_fast(slow_ptr->next, fast_ptr, dat,ctr);
			break;
		}
		fast_ptr = fast_ptr->next;
	}
	if (!sig)
		sig=remove_fe_fast(slow_ptr,fast_ptr,dat,ctr);
	++ctr;
	if (ctr==dat)
		return slow_ptr->data;
	return sig;
} */



void LLL::display(void)const{
	Node * curr = head;
	int i = 1;

	while(curr){
		printf("Node %d contains %d\n", i, curr->data);
		curr = curr->next;
		++i;
	}
	return;
}


LLL::~LLL(){
	while(head){
		Node * temp = head;
		head = head->next;
		delete temp;
	}
	tail = NULL;
}
	
