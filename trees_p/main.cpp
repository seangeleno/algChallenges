#include "tree.hpp"

void display(tree*& t){
	int sel;
	printf("1 pre, 2 in, 3 post\n");
	scanf("%d",&sel);
	switch(sel){
		case 1:
			t->display_pre();
			break;
		case 2:
			t->display_in();
			break;
		case 3:
			t->display_post();
			break;
		default:
			break;
	}
	return;
}



int main(){
	int size, up_lim;
	int select;
	scanf("%d",&size);
	scanf("%d",&up_lim);
	tree * t = new tree(size, up_lim);
	do{
		printf("1 to display, 2 to insert, 3 to remove, 0 to exit\n");
		scanf("%d",&select);


		switch(select){
			case 1:
				display(t);
				break;
			case 2: 
				scanf("%d",&up_lim);
				t->insert(up_lim);
				break;
			case 3:
				scanf("%d",&up_lim);
				t->remove(up_lim);
				break;
			case 0:	
				break;
			default:
				break;
		}
	}while(select!=0);
	delete t;

	return 0;
}


