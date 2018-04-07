#pragma once

#include <iostream>
#include <string.h>
#include <stdlib.h>
using std::cout;
using std::cin;
using std::istream;
using std::ostream;
 
class string{
private:
	int __cap;
	char* __str;
public:
	string();
	string(const char*);

	string(const string &);
	~string();
	
		
	string& operator=(const string &);
	string& operator+=(const string &);
	string& operator +=(const char* );
	string operator +(const string&) const;
	friend ostream& operator<<(ostream& os, const string& str);
	friend istream& operator>>(istream& is,  string& str);
};


