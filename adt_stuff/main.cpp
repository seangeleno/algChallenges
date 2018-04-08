#include "string.hpp"
#include "table.hpp"

#include <iostream>

void concat(string & str1, string & str2, table & storage){
	int select;
	query query1, query2;
	cout << "1 to retrieve an item and then concatenate, " <<
		"2 to concatenate two retrieved" << std::endl;
	cin >> select;
	cin.ignore(400,'\n');


	if (select==1){
		cin >> str1;


		
		query1 = storage.retrieve(str1);
		query1.display();
		cout << "modify" << std::endl;
		cin >> str1;
		str2 = query1.get_name();
		str2+=str1;
		if(query1.set_name(str2)){
			cout << "successful modification" << std::endl;
			storage.insert(query1);
		}
		return;
	}
	else if (select == 2){
		cin >> str1;
		query1 = storage.retrieve(str1);
		query2 = storage.retrieve(str2);
		query1.join(query2);
		storage.remove(str1);
		storage.remove(str2);
		storage.insert(query1);
	}
	return;
}

int main(){
	query query1;
	string str1, str2;
	table storage;
	int select;
	do{
		cout << "1) input string to table\n2) display table\n3) concatenate 2 strings\n0) exit\n" << std::endl;
		cin >> select;
		cin.ignore(400,'\n');
		switch(select){
			case 1:
				cin >> str1 >> str2;
				query1.set_name(str1);
				query1.set_date(str2);
				storage.insert(query1);
				break;
			case 2:
				storage.display();
				break;
			case 3:

				concat(str1,str2,storage);
				break;
			case 0:
				break;
			default:
				cout << "enter a valid option" << std::endl;
				break;

		}
	} while( select );
				
	return 0;
}
