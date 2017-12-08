#include <iostream>

using namespace std;

long long int naive_fib( int );

int main(){
	int nth_term;
	cout << "enter the nth term of the fibonacci sequence you wish to retrieve" << endl;
	cin >> nth_term;
	cin.ignore(400,'\n');









	long long int output = naive_fib(nth_term);
	cout << "the " << nth_term << "th term is " << output << endl;
	return 0;

}

long long int naive_fib(int depth){
	if (depth <= 1)
		return 1;
	return naive_fib(depth-1) + naive_fib(depth-2);
}