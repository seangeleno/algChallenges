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
	
	int size(void)const;	
	int sounding_split(const char)const;
	int split(const char, string*&)const;

	string& operator=(const string &);
	string& operator=(const char*);
	string& operator+=(const string &);
	string& operator +=(const char* );
	string operator +(const string&) const;
	string operator +(const char[]) const;
	bool    operator !=(const string&)const;
	char&   operator [](const int) const;
	bool operator ==(const string&)const;
	friend ostream& operator<<(ostream& os, const string& str);
	friend istream& operator>>(istream& is,  string& str);

	char * get_str(void) const{
		return __str;
	}
};


