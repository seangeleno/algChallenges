#pragma once

#include <stdarg.h>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;


#include "string.hpp"


class p_tuple{
public:
	char m_type;
	string m_name;
	p_tuple(void) : m_type(0), m_name(){}
	p_tuple(string ins, string inc) : m_name(ins), m_type(inc[0]){}
	/*p_tuple(string ins, string inc){
		char* temp = ins.get_str();
		m_name = new char[strlen(temp)+1];
		strcpy(m_name,temp);
		m_type = inc[0]; 
	}*/

};










class table{
public:
	p_tuple * m_prototype;
	string m_name;
	int	m_n_items;


	table(void);
	table(int nargs, ...);
	table(string, p_tuple ** );
	table(const int, const string, p_tuple *);
	~table(void);

	void display_schema(void)const;
};

