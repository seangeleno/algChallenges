#include <stdio.h>
#include <stdlib.h>
#include "string.hpp"


class entry{
public:
	string m_name;
	char m_type;

	entry(void)
		: m_type(0){}
	entry(string in_name, char in_type) 
		: m_name(in_name), m_type(in_type){}
	void virtual display(void)const{
		printf("%s | %c", m_name.get_str(), m_type);	
	
	}	


	string virtual disp_data(void)const =0;
};


class entry_int : public entry{
public:
	int m_data;

	entry_int(void) : m_data(0) {}
	entry_int(string in_name, char in_type, int in_data)
		: m_data(in_data), entry(in_name, in_type){}
	
	void display(void) const{
		entry::display();
		printf(" | %d\n", m_data);
	}

	string disp_data(void) const override{
		char * array_ = new char[10];
		snprintf(array_, 10, "%d",m_data);
		string out(array_);
		delete array_;
		return out;
	}
};	


class entry_str : public entry{
public:
	string m_data;

	entry_str(void) : m_data(){}
	entry_str(string in_name, char in_type, string in_data) 
		: m_data(in_data), entry(in_name, in_type){}

	void display(void) const{
		entry::display();
		printf(" | %s\n", m_data.get_str());
	}
	string disp_data(void) const override{
		return m_data;
	}
};


class entry_time : public entry{
public:
	string m_data;
	entry_time(void) : m_data(){}
	entry_time(string in_name, char in_type, string in_data)
		: m_data(in_data), entry(in_name, in_type){}
	void display(void) const{
		entry::display();
		printf(" | %s\n", m_data.get_str());
	}

	string disp_data(void) const override{
		return m_data;
	}	
};



class entry_float : public entry{
public:
	float m_data;
	entry_float(void) : m_data(0){}
	entry_float(string in_name, char in_type, float in_data)
		: m_data(in_data), entry(in_name, in_type) {}
	void display(void) const{
		entry::display();
		printf(" | %f\n", m_data);}

	string disp_data(void) const override{
		char* array_ = new char[10];
		snprintf(array_, 10, "%f", m_data);
		string out(array_);
		delete array_;
		return out;
	}
};
