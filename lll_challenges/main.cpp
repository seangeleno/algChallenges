#include <string>
#include <list>
#include <map>
#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <functional>
#include <cstdio>
using namespace std;








mutex mtx;

void insertion(list<string>& lis, string str ){
	//mtx.lock();	
	lis.push_back(str);
	//mtx.unlock();
}

void retrieve(list<string>& lis, int pos){
	list<string>::iterator iter = lis.begin();
	string str;
	short int  sel;
	for (int i = 0; (i < pos) && (iter != lis.end()) ; ++i)
		++iter;
	cout << *iter << endl;
	cout << "modfiy?" << endl;
	cin >> sel;
	if (sel == 1)
	{
		cin.clear();
		cout << "enter the term." << endl;
		cin.ignore(400,'\n');
		getline(cin, str, '\n');
		lis.insert(iter, str);
		lis.erase(iter);
	}
	else
		return;
	return;

}


void menu(list<string> & lis){
	std::list<string>::iterator iter;
	std::list<string>::reverse_iterator r_iter;
	
	int sel;
	do{
		cout << "1 to show list, 2 to show reverse, 0 to exit" << endl;
		cin >> sel;
		switch(sel){
			case 1:
				for (iter = lis.begin() ; iter != lis.end(); ++iter)
					cout << *iter << endl;
				break;
			case 2:
				for (r_iter = lis.rbegin(); r_iter != lis.rend(); ++r_iter)
					cout << *r_iter << endl;
				break;
			default:
				break;
		}
	}while(sel != 0);
	return;
}

void elim_str(list<string>& lis, const string str, const int offset, const int id){

//Doesnt work, pointers get rearranged following deletion
	int cnt = 0;	
	auto iter = lis.begin();

	while(cnt < offset*id && iter!=lis.end()){
		++iter;
		++cnt;
	}
	for (int i = 0; i < offset; ++i){
		if (iter == lis.end())
			break;
		string inspect = *iter;
		char loc = str[0];
		mtx.lock();
		printf("to delete: %c\ncurrent element: %c\n: id %d\nposition %d in list\n\n",loc,inspect[0], id, id*offset+i);

		mtx.unlock();
		if (inspect[0] == loc)
			lis.erase(iter);

	}
	return;
}

void launch(list<string>& lis, const string begins_with){
	thread* threads[4];
	int partitions = lis.size();
	int offset = partitions/std::thread::hardware_concurrency();
	printf("offset : %d\ntotal size: %d\n",offset,partitions);
	for (int i =0; i < 4; ++i)
		threads[i] = new thread(elim_str, std::ref(lis), begins_with, offset, i);
	for (int i = 0; i < 4; ++i){
		threads[i]->join();
		delete threads[i];
	}
	
	return;
}





int main(){
	list<string> str_lis;
	
	string str;
	int count=0;
	int retr_loc;
	do{
		printf("enter strings until you wanna end the program with 0. enter e for menu\n");
		getline(cin, str, '\n');
		if (str=="\n")
			continue;
		if (str == "e")
			menu(std::ref(str_lis));
		else if (str == "get"){
			cin >> retr_loc;
			if (!(retr_loc < 0) || retr_loc > str_lis.size())
				retrieve(std::ref(str_lis), retr_loc);
			else cout << "exceeds list bounds" << endl;
		}
		else if (str == "launch"){
			string b_w;
			cout << "eliminate those data which begin with....?" << endl;
			cin >> b_w;
			launch(std::ref(str_lis),b_w);
		}
		else
			insertion(std::ref(str_lis), str);
		cin.clear();
		cout.clear();

	}while(str!="0");
	







	list<string>::iterator iter = str_lis.begin();
	while(iter != str_lis.end()){
		cout << *iter << endl;
		++iter;
	}

	return 0;
}
