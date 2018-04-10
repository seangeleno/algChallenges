#include "tree.hpp"

tree::tree() : root(NULL){}
tree::tree(const int sz, const int upper_bound){
	root = NULL;
	int supply;
	for (int i = 0; i < sz; ++i){
		supply = rand() % upper_bound;
		insert(supply);
	}
}







int tree::insert(const int d){
	if (!root){
		root = new node(d);
		return 1;
	}

	return insert(root,d);
}


int tree::insert(node*& curr, const int d){
	if (!curr){
		curr = new node(d);
		return 1;
	}
	if (d < curr->dat)
		return insert(curr->l, d);
	else 
		return insert(curr->r, d);
}

int tree::remove(const int d){
	if (!root)
		return 0;
	return remove(root, d);
}

int tree::remove(node*& curr, const int d){
	if (!curr)
		return 0;
	else if (curr->dat == d){
		node * temp,* l_branch, * r_branch;
		l_branch = curr->l;
		r_branch = curr->r;

		if (seek_ios(curr->r, temp)) {
			delete curr;
			curr = temp;
			if (l_branch && !curr->l)
				curr->l = l_branch;
			else
				insert(curr->l, l_branch);
			if (r_branch && !curr->r)
				curr->r = r_branch;
			else if (!(curr->r && !r_branch))
				insert(curr->r, r_branch);
			return 1;
		}
		delete curr;
		if (r_branch){
			curr = r_branch;
			insert(curr, l_branch);
			return 1;
		}
		else if (l_branch){
			curr = l_branch;
			return 1;
		}
		else{
			curr = NULL;
			return 1;
		}

	}
	else if (d < curr->dat)
		return remove(curr->l, d);
	else return remove(curr->r, d);
}





int tree::insert(node*& curr, node*& to_set){
	//used to insert from removed node, since previous stack frame
	//maintains the memory address despite it being set off the heap
	if (!curr){
		curr = to_set;
		return 1;
	}
	if (to_set->dat < curr->dat)
		return insert(curr->l, to_set);
	else 
		return insert(curr->r, to_set);
}
void tree::display_pre(void){
	return pre(root);
}
	

void tree::display_in(void){
	return in_(root);
}


void tree::display_post(void){
	return post(root);
}


int tree::seek_ios(node* curr, node*& mem_loc){
	if (!curr)
		return 0;
	node * par;
	while(curr->l) {
		par = curr;
		curr = curr->l;
	}
	par->l = NULL;
	mem_loc = curr;

	return 1;
}


void tree::pre(node*& curr){
	if (!curr)
		return;
	printf("%d\n",curr->dat);
	pre(curr->l);
	pre(curr->r);
	return;
}


void tree::in_(node*& curr){
	if (!curr)
		return;
	in_(curr->l);
	printf("%d\n",curr->dat);
	in_(curr->r);
	return;
}



void tree::post(node*& curr){
	if (!curr)
		return;
	post(curr->l);
	post(curr->r);
	printf("%d\n",curr->dat);
	return;
}


int tree::destr_tree(node*& curr){
	if (!curr)
		return 0;
	destr_tree(curr->l);
	destr_tree(curr->r);
	return 1;
}


tree::~tree(void){
	destr_tree(root);
}

