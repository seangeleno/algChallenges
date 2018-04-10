
#include "lll.hpp"


/*void tree_rand(void){
	int sel;
	int dat;
	printf("enter the number of elements, and the max they can be\n");
	scanf("%d",&sel);
	scanf("%d",&dat);
	BinTree tree = new BinTree(sel,dat);
	do{
		printf("this explores data structures.\n 1) insert to lll, 2) append,"\
		"3) remove all of the item, 4) remove item at position n in the list\n" \
		"5) remove item at -n position in the list.\n\n");
		scanf("%d",&sel);

		switch (sel){

			case 1:
				scanf("%d",&dat);
				tree->insert(dat);
				break;
			case 2:
				scanf("%d",&dat);
				tree->append(dat);
				break;
			case 3:
				scanf("%d",&dat);
				tree->remove_all(dat);
				break;
			case 4:
				scanf("%d",&dat);
				tree->remove_at(dat);
				break;
			case 5:
				scanf("%d",&dat);
				tree->remove_from_end(dat);
				break;
			case 6:
				tree->display();
				break;
			default:
				break;
		}
	}while(sel!=0);
	delete tree;
	return;
}
*/


void LLL_rand(void){
	int sel;
	int dat;
	printf("enter the number of elements, and the max they can be\n");
	scanf("%d",&sel);
	scanf("%d",&dat);
	LLL * lll = new LLL(sel,dat);
	do{
		printf("this explores data structures.\n 1) insert to lll, 2) append,"\
		"3) remove all of the item, 4) remove item at position n in the list\n" \
		"5) remove item at -n position in the list. 6) display, 7) recur to pos of del\n"\
		"8) 0) end\n\n");
		scanf("%d",&sel);

		switch (sel){

			case 1:
				scanf("%d",&dat);
				lll->insert(dat);
				break;
			case 2:
				scanf("%d",&dat);
				lll->append(dat);
				break;
			case 3:
				scanf("%d",&dat);
				lll->remove_all(dat);
				break;
			case 4:
				scanf("%d",&dat);
				lll->remove_at(dat);
				break;
			case 5:
				scanf("%d",&dat);
				lll->remove_from_end(dat);
				break;
			case 6:
				lll->display();
				break;
			case 7:
				scanf("%d",&dat);
				lll->remove_at_r(dat);
				break;
			case 8:
				scanf("%d",&dat);
				dat = lll->remove_fe_fast(dat);
				printf("%d\n",dat);
				break;
			default:
				break;
		}
	}while(sel!=0);
	delete lll;
	return;
}



int main(){
	LLL lll;
	int sel;
	int dat;
	do{
		printf("this explores data structures.\n 1) insert to lll, 2) append,"\
		"3) remove all of the item, 4) remove item at position n in the list\n" \
		"5) remove item at -n position in the list.\n\n");
		scanf("%d",&sel);

		switch (sel){

			case 1:
				scanf("%d",&dat);
				lll.insert(dat);
				break;
			case 2:
				scanf("%d",&dat);
				lll.append(dat);
				break;
			case 3:
				scanf("%d",&dat);
				lll.remove_all(dat);
				break;
			case 4:
				scanf("%d",&dat);
				lll.remove_at(dat);
				break;
			case 5:
				scanf("%d",&dat);
				lll.remove_from_end(dat);
				break;
			case 6:
				lll.display();
				break;
			case 7:
				LLL_rand();
				break;
		
			default:
				break;
		}
	}while(sel!=0);

	return 0;
}
