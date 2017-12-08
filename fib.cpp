#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<int,long long int>::const_iterator fib( unordered_map<int,long long int>&, int );

int main(){
	int nth_term;
	unordered_map<int,long long int> map_in;
	cout << "enter the nth term of the fibanocci sequence you wish to return" << endl;
	cin >> nth_term;
	cin.ignore(400, '\n');


	unordered_map<int,long long int>::const_iterator output = fib( map_in, nth_term);
	cout << "the " << nth_term << " of the fibanocci sequence is " << output->second << " " << endl;
	return 0;
}














unordered_map<int,long long int>::const_iterator fib(unordered_map<int,long long int>& dyn_dict, int depth ){
	if (depth <= 1) {
		unordered_map<int,long long int>::const_iterator base_case_K = dyn_dict.find( depth );
		if (base_case_K == dyn_dict.end())
			dyn_dict[ depth ] = 1;
		return dyn_dict.find( depth );
	}

	unordered_map<int,long long int>::const_iterator found_key = dyn_dict.find( depth );
	if (found_key == dyn_dict.end()){
		dyn_dict[ depth ] = ( fib( dyn_dict, depth-1)->second + fib( dyn_dict, depth-2)->second );
		return dyn_dict.find( depth );
	}
	return dyn_dict.find(depth);
}