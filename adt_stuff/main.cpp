#include "string.hpp"
#include "table.hpp"

#include <iostream>

int main(){
	char buffer[300];
	string str1, str2;
	string str3;
	table storage;
	cin >> str1;
	cout << str1 << std::endl;

	cin.get(buffer,299,'\n');
	cin.ignore(300,'\n');
	char* _in = new char[strlen(buffer)+1];
	strcpy(_in,buffer);
	str2 = str1+=_in;


	storage.insert(str2);	
	str3 = str1 + " yes hi1 ";
	cout << str3 << std::endl;
	storage.insert(str3);
	for (int i = 0; i < 5; ++i)
		str2+=str1;
	cout << str2 << std::endl;
	storage.insert(str1);
	storage.insert(str2);

	storage.display();
	delete[] _in;
	return 0;
}
