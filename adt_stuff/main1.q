#include <stdio.h>
#include <string.h>

#include "string.hpp"
#include "table.hpp"


#include <iostream>
using std::cin;




int main(){
	table* tables[5];
	string in_n, in_s, in_s2;
	char in_c;
	int in_d, sel;
	//entry_int * ei;
	//entry_str * es;
	int cnt = 0;
	int p_cnt = 0;
	p_tuple ** p_bus = new p_tuple*[5];
	p_tuple i_1,  i_2, i_3;


	char * name_in_c;
	do{
		printf("1 to enter new table, 2 to display specific table schema, 0 to exit\n");
		cin >> sel;

		cin.ignore(400,'\n');

		
		switch(sel)
		{
			case(1):
				printf("enter 0 to submit new schema\n");
				while(1){	
					cin >> in_s;
					if (in_s == string("0"))
						break;
					cin >> in_s2;
					p_bus[p_cnt] = new p_tuple(in_s, in_s2);
					p_cnt++;

				}
				tables[cnt] = new table(string("hello there"),p_bus);		
				memset(p_bus, 0, 5*sizeof(p_tuple *));
				cnt++;
				break;

			case 2:
				printf("enter the name of the table to fetch\n");
				cin >> in_s;
				for (int i = 0; i < cnt; ++i){
					if (in_s == tables[i]->m_name)
						tables[i]->display_schema();
				}
				break;
			case 3:
				i_1 = p_tuple(string("master"),string("S")), 
				i_2 = p_tuple(string("TYPE"), string("C"));
				i_3 = p_tuple(string("TIME"), string("T"));
				name_in_c = new char[5];
				strcpy(name_in_c,"name");
				tables[cnt] = new table(4, name_in_c , (&i_1), (&i_2), (&i_3));
				delete name_in_c;
				cnt++;
				break;
			default:
				break;

		}

	}while(sel);

	for (int i = 0; i < cnt; ++i)
		delete tables[i];
	delete[] p_bus;
	return 0;
}
