#include "string.hpp"

string::string(){
	__cap = 25;
	__str = new char[__cap];
	memset(__str,0,sizeof(char)* __cap);
}







string::string(const char* in_) :
	__cap(strlen(in_)+1), 
	__str(new char[__cap])

{
	strcpy(__str,in_);
}


string::string(const string& other) : 
	__cap(other.__cap),
	__str(new char[__cap])
{
	memcpy(__str,other.__str,__cap);
}


int string::size(void)const{
	return __cap;
}


string string::operator+(const string& other)const{
	char buffer[500];
	memset(buffer,0,sizeof(char)*500);
	memcpy(buffer,__str,__cap);
	memcpy(buffer+__cap,other.__str,other.__cap);
	char * n_s = new char[strlen(buffer)+1];
	strcpy(n_s,buffer);
	string* out = new string(n_s);
	return (*out);
}


string string::operator +(const char other[])const{
	char buffer[500];
	memset(buffer, 0, sizeof(char)*500);
	memcpy(buffer,  __str,  __cap-1);
	memcpy(buffer + __cap-1,  other,  strlen(other));


	char * n_s = new char[strlen(buffer)+1];
	strcpy(n_s, buffer);
	string* out = new string(n_s);
	return (*out);
}


string& string::operator +=(const string& other){
	__str = (char*) 
		realloc(__str, sizeof(char) * (__cap-1) * (other.__cap-1)+1);
	__cap += other.__cap - 1;
	strcat(__str, other.__str);
	return *this;
}


string& string::operator +=(const char* other){
	__str = (char*)
		realloc(__str, sizeof(char) * (__cap-1) * strlen(other) +1);
	__cap = strlen(other) + __cap;
	strcat(__str,other);
	return *this;
}


string& string::operator =(const string &other){
	if (__str)
		delete[] __str;
	__str = new char[other.__cap];
	__cap = other.__cap;
	memcpy(__str,other.__str,__cap);
	return *this;
}


string& string::operator =(const char* other){
	if (__str)
		delete[] __str;
	__cap = strlen(other) + 1;
	__str = new char[__cap];
	memcpy(__str,other,__cap);
	return *this;
}

bool string::operator !=(const string& other) const{
	if (strcmp(__str, other.__str)!=0)
		return false;
	return true;
}
char& string::operator[](const int i)const{
	char c = '\0';
	if (i > __cap)	return __str[0];
	return __str[i];
}


string::~string(){
	if (__str)
		delete[] __str;
}


ostream& operator << (ostream& os, const string& str){

	os << str.__str;
	return os;
}



istream& operator >>(istream& is, string& str){
	char buffer[200];
	is.get(buffer,199,'\n');
	is.ignore(400,'\n');
	if (str.__str)
		delete[] str.__str;
	str.__str = new char[strlen(buffer)+1];
	str.__cap = strlen(buffer);
	strcpy(str.__str,buffer);
	return is;
}



