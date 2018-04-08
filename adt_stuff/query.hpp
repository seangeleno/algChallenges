#pragma once
#include "string.hpp"

using std::cout;
using std::cin;

class query{
private:
	string __name;
	string __date;
public:
	query(void);
	query(const string&, const string&);

	query(int);	
	~query();

	int join(const query&);
	int set_name(const string&);
	int set_date(const string& );
	string get_name(void)const;
	string get_date(void)const;


	int run_check(const string&)const;
	void display(void)const;	
	query& operator=(const query& other);

};

