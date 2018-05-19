#include "table.hpp"


table::table(void) : m_prototype(NULL), m_name(), m_n_items(0){}


table::table(int nargs, ...){
	va_list ap;
	va_start(ap, nargs);

	char * temp_name = va_arg(ap, char*);
	m_name = temp_name;



	m_prototype = new p_tuple[nargs];
	--nargs;

	p_tuple * can_tup;
	m_n_items = nargs;
	for (int i = 0; i < nargs; ++i){
		can_tup = va_arg(ap,p_tuple*);
		m_prototype[i] = *can_tup;
	}
	va_end(ap);

}

void table::display_schema(void)const{
	cout << "{\n";
	for (int i = 0; i < m_n_items; ++i)
		cout << "\t" << m_prototype[i].m_name <<\
			" " << m_prototype[i].m_type << "," << endl;
	cout << "}" << endl;
}


//table::add_to(const entry* data){}	
table::table(const int nargs, const string name, p_tuple * p_bus){
	m_name = name;
	m_n_items = nargs;
	m_prototype = new p_tuple[nargs];

	for (int i = 0; i < m_n_items; ++i){
		m_prototype[i].m_type = p_bus[i].m_type;
		m_prototype[i].m_name = p_bus[i].m_name;
	}

	return;

}


table::table(string in_name, p_tuple ** p_bus) : m_name(in_name)
{
	m_prototype = new p_tuple[5];

	int i = 0;
	while(p_bus[i] != NULL)
	{
		m_prototype[i] = *p_bus[i];
		++i;
	}


	m_n_items = i;

}
	
table::~table(void){
	delete[] m_prototype;
}
