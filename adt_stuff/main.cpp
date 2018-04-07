#include "string.hpp"
#include <iostream>

int main(){
	char buffer[300];
	string str1, str2;
	cin >> str1;
	cout << str1 << std::endl;

	cin.get(buffer,299,'\n');
	cin.ignore(300,'\n');
	char* _in = new char[strlen(buffer)+1];
	strcpy(_in,buffer);
	str2 = str1+=_in;



	cout << str2 << std::endl;
	delete[] _in;
	return 0;
}
