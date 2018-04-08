#include "query.hpp"

query::query(){
	__name = "";
	__date = "0/0/0";
}


query::query(const string& name, const string& date){
	__name = name;
	if (run_check(date))  
		__date = date;
}

query& query::operator=(const query& other){
	__name = other.__name;
	__date = other.__date;

	return *this;
}

query::query(int a){
	__name = "\0";
	__date = "\0";
}

int query::set_name(const string& new_name){
	__name = new_name;
	return 1;
}

string query::get_name(void) const{
	return __name;
}

int query::set_date(const string& new_date){
	__date = new_date;
	return 1;
}

string query::get_date(void) const{
	return __date;
}


int query::join(const query& other){
	
	__name+=" ";
	__name+=other.__name;
	__date+=" thru ";
	__date+=other.__date;
	
	return 1;
}


int query::run_check(const string& c_d) const{
	char ch;
	for (int i = 0; i < 7; ++i){
		if ((i > -1 && i < 3 ) || (i > 3 && i < 6 ) || i > 6 ){
			ch = c_d[i];
			if (ch < '0' || ch > '9')
				return 0;
		}
		else if ( i == 3 || i == 6 ){
			ch = c_d[i];
			if (ch!='/')
				return 0;
		}
	}
	return 1;
}

void query::display(void)const{
	cout << __name <<"\ndate: " << __date << std::endl;		
}


query::~query(){
	cout << "deletion successful" << std::endl;
}
