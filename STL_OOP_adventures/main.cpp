#include "Tree.hpp"
#include "Node.hpp"

#include <iostream>
using namespace std;

int main(){
	Tree main_tree = Tree("hello there");
	











	int  __case = 1;	
	while(__case){
	cout << "1 insert family with genus and phylum\n2 insert new phylum\n" << 
	"3 retrieve family\n4 retrieve genus\n5 retrieve species\n6 display all\n" <<
	"7 to add a path between nodes\n" << 
	"0 exit" << endl;
	cin >> __case;

	string in_family, in_genus, in_phylum;
	string rx_fam;

	unordered_map<string, vector<uint32_t> > family_map; //note that these are created and destroyed per loop
	vector<uint32_t> species_list; //this cost can theoretically be overriden if defined outside the loop
	uint32_t in_species =1;
	switch(__case){
		case 1:
			cout << "BETWEEN INPUTS PRESS ENTER\nfamily, genus, species(number)" << endl;
			cin >> in_family >> in_genus >> in_species;
			main_tree.insert(in_family,in_genus,in_species);
			break;

		case 2:
			cout << "Enter the new phylum" << endl;
			cin >> in_phylum;
			main_tree.insert(in_phylum);
			break;


		case 3:
			cout << "enter the family" << endl;
			cin >> in_family;
			family_map = main_tree.retrieve_map(in_family);
			for ( auto i = family_map.begin(); i != family_map.end(); ++i){
				cout << "genus " << i->first <<" contains" << endl;
				auto local_vec = i->second;
				for (auto j = 0; j < local_vec.size(); ++j ){
					cout << "\t" << local_vec[j] << endl;
				}
			}
			break;


		case 4:
			cout << "BETWEEN INPUTS PRESS ENTER\nfamily, genus" << endl;
			cin >> in_family >> in_genus;
			species_list = main_tree.retrieve(in_family, in_genus);
			cout << "retrieved list of species belonging to genus " << in_genus << " contains" << endl;
			for (auto i = 0; i < species_list.size(); ++i)
				cout << "\t"<<species_list[i]<<endl;
			break;
		

		case 5:
			cout << "family genus species" << endl;
			cin >> in_family >> in_genus >> in_species;
			break;



		case 6:
			main_tree.display_all();
			break;



		case 7:
			cout << "enter the family to connect, and then the family to connect to" << endl;
			cin >> in_family >> rx_fam;
			main_tree.insert_path(rx_fam, in_family);
			break;



		default:
			break;
		}

		cout<<endl;
	}
	return 0;
}
