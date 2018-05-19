#include <stdio.h>
#include <string.h>

#include "string.hpp"
#include "entry.hpp"
#include <iostream>
using std::cin;




int main(){
	entry* entries[5];
	string in_n, in_s;
	char in_c;
	int in_d, sel;
	entry_int * ei;
	entry_str * es;
	int cnt = 0;
	do{
		printf("1 to enter type, 2 to display all, 0 to exit\n");
		cin >> sel;

		cin.ignore(400,'\n');

		
		switch(sel)
		{
			case(1):
				printf("fill the three parameter fields\n");
				cin >> in_n >> in_c;
				cin.ignore(400,'\n');
				switch(in_c){
					case 'd' :
						cin >> in_d;
				cin.ignore(400,'\n');
						ei = new entry_int(in_n, in_c, in_d);
						entries[cnt] = ei;
						cnt++;
						break;
					case 's':
						cin >> in_s;
				cin.ignore(400,'\n');
						es = new entry_str(in_n, in_c, in_s);
						entries[cnt] = es;
						cnt++;
						break;
					default:
						printf("d or s\n");
						break;
				}
				break;
			case(2):
				for (int i = 0; i < cnt; ++i)
				{
					char c_ = entries[i]->m_type;
					switch(c_){
						case 'd':
							ei = dynamic_cast<entry_int*>(entries[i]);
							ei->display();
							break;
						case 's':
							es = dynamic_cast<entry_str*>(entries[i]);
							es->display();
							break;
						default:
							break;
					}
				}
				break;

			default:
				break;
		}
	}while(sel);

	for (int i = 0; i < cnt; ++i)
		delete entries[i];

	return 0;
}
