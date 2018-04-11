#include "tree.hpp"
#include <time.h>
#include <string.h>
tree::tree() : root(NULL){}
tree::tree(const int sz, const int upper_bound){
	root = NULL;
	int supply;
	srand(time(NULL));
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
	if(root->dat == d){
		node * temp;
		node* l_branch = root->l;
		node* r_branch = root->r;
		delete root;
		if(seek_ios(r_branch,temp)){
			root = temp;
			if (temp->l)
				insert(root,temp->l);
			if (temp->r)
				insert(root,temp->r);
			root->l = l_branch;
			root->r = r_branch;
			return 1;
		}
		root = r_branch;
		return 0;
	}
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

int tree::get_num_children(node* curr,int & depth, int counter){
	if(!curr)
		return 0;
	if (counter>depth) depth = counter;
	if (!curr->l && !curr->r)
		return 1;
	int cnt = get_num_children(curr->l,depth,counter+1);
	cnt    += get_num_children(curr->r,depth,counter+1);
	return cnt;
}


void tree::display_pre(void){
	int depth = 0;
	int children = get_num_children(root,depth,0);
	int avg = (int)children/2;
	int bounds = depth*children+depth;
	char * screen = new char[bounds];
	memset(screen,32,sizeof(char)*bounds);
	for (int i = depth; i < bounds; i*=depth)
		screen[i-1] = '\n';
	screen[bounds-1]='\0';
	printf("%s",screen);
	int incr = avg*depth;
	int offset = 0;
	int deepest = depth;
	printf("children: %d, avg: %d\n", children, avg);
	pre(root,0,incr,screen,bounds,offset,deepest,avg);
	for(int i = 0; i < bounds; i*=depth){
		for (int j = 0; j < depth; ++j){
			printf("%c",screen[i*depth+j]);
		}
	}
	printf("\n");


	delete[] screen;
}
	

void tree::display_in(void){
	 in_(root,0);
	 printf("\n");
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


void tree::pre(node*& curr,int depth, int incr, char *& screen, \
	const int bounds, const int box_bound, const int deepest, const int avg)
{
	if (!curr)
		return;

	

	incr/=(2*depth);

	char in = curr->dat + 42;
	int loc = incr+deepest*incr;
	int i = depth*incr+1;
	for (i; i < loc+depth+1; ++i)
		screen[i] = '-';
	screen[i] = in;
	pre(curr->l,depth+1,incr,screen,bounds,box_bound,deepest,avg);
	pre(curr->r,depth+1,incr,screen,bounds,box_bound,deepest,avg);
	return;
}


void tree::in_(node*& curr,int depth){
	if (!curr)
		return;
	in_(curr->l,depth+1);
	char buffer[25];
	memset(buffer,0,25);
	memset(buffer,'-',depth+1);
	buffer[0]='\n';
	printf("%s%d\n",buffer,curr->dat);
	in_(curr->r,depth+1);
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

