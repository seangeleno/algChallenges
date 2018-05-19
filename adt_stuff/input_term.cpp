#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "table.hpp"
#include "lookup.hpp"
#include "string.hpp"
using std::cout;
using std::cin;
using std::endl;
bool str_to_tup(const int nargs, string* input, p_tuple *& output){
	output = new p_tuple[nargs];
	for (int i = 0; i < nargs; ++i){
		int els_from_split = input[i].sounding_split(' ') + 1;
		string * ns = new string[els_from_split];
		input[i].split(' ' , ns);
		
		
		output[i].m_name = ns[0];
		output[i].m_type = ns[1][0];
		delete[] ns;
	}
	return true;
}


int create_table(lookup & mp){
	char c;
	int i = 0, cnt = 0;
	char * buffer = new char[2048];
	string * input = new string[64];
	string __name;
	cout << "NAME ";
	cin >> __name;


	while(read(STDIN_FILENO, &c, 1) && c != '}'){
		if (c == ','){
			input[cnt] = buffer;
			memset(buffer,0,sizeof(char)*2048);
			i = 0;
			cnt++;
		}
		
		else{
			buffer[i] = c;
			++i;
		}	
	}
	p_tuple * output;
	if(str_to_tup(cnt, input, output))
		mp.add_to(cnt, __name, output );
	delete[] input;
	delete[] buffer;
	cout << "insertion successful. now in main\n" << endl;
	return 1;	
		
}


void select_table(lookup & mp){
	string in_name;

	cout << "enter the name of the table" << endl;
	cin >> in_name;

	table tbl = mp.retrieve(in_name);
	tbl.display_schema();

	return;
}







int main()
{
	char buffer[2048];
	char c;
	int cnt;
	lookup mp(53);
	cout << "welcome to a sql derivative!!" << endl;
	cout << "enter CREATE to make a new table.  enter SELECT to grab a schema" << endl;
	while(read(STDIN_FILENO, &c, 1) && (strcmp(buffer, "quit")!=0))
	{
		if (c != 32 && c!= '\n'){
			buffer[cnt] = c;
			cnt++;
		}
		if ((strcmp(buffer, "CREATE") == 0) || 
				(strcmp(buffer, "SELECT") == 0))
		{
			if (strcmp( buffer, "CREATE" ) == 0)
				create_table(mp);
			else if (strcmp(buffer, "SELECT") == 0)
				select_table(mp);
			
			cnt = 0;
			memset(buffer, 0, sizeof(char) * 2048);
		}
	}

	return 0;
}
