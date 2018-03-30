#include <iostream>
#include <map>
#include <utility>
#include <time.h>
using namespace std;

char ** generate_maze( int row, int col );
int make_maze(int i, int j, int maxi, int maxj, char ** layout, int depth, \
	int counter, map<pair<int, int>, bool> &map_in_prog);
int retrieve(int i, int j, int maxi, int maxj, int ** layout, \
	map< pair<int,int>, bool> & in_map);

int  make_maze(int i, int j, int maxi, int maxj, char ** layout, int depth,
	int counter, map< pair<int,int>, bool> & map_in_prog )
{
	if (i<0 || j < 0 || i == maxi || j == maxj ) //check if the calls have explored 
	//a location exceeding the bounds of the matrix
		return 0;
	pair<int,int> local_pair = make_pair(i,j); 
	/*creating a local structure to contain the pairing.
	aim to reduce redundant creation of data structuresl; this can be very 
	costly, especially at scale*/
	if ( map_in_prog[local_pair] == true)
		return 0;
	else map_in_prog[local_pair] = true;
	
	if (layout[i][j] == '9')
		return 1; //we have reached the objective; return up the stack

	else if ( (depth < 3|| ++counter > 2) && layout[i][j] == '0'){
	/*this section aims to make the stochastic process of maze initialization
	a bit more maze-like. the program then chooses a random direction to tunnel
	a new walk*/
		layout[i][j] = '1';
		counter = 0;

		int sel = rand()%4;
		switch(sel){
			case 0:
				return make_maze( i+1, j, maxi, maxj, layout, depth+1, counter, map_in_prog);
			case 1:	
				return make_maze( i-1, j, maxi, maxj, layout, depth+1, counter, map_in_prog );
			case 2:
				return make_maze( i, j+1 , maxi, maxj, layout, depth+1, counter, map_in_prog );
			case 3:
				return make_maze( i, j, maxi, maxj, layout, depth+1, counter, map_in_prog );
			}
		}
	
	//This section is made up entirely of recursive calls to different locations
	//in the maze matrix
	else if (make_maze( i + 1, j, maxi, maxj, layout, depth+1, counter, \
		map_in_prog ) == 1)
			return 1;

	else if (make_maze( i-1, j, maxi, maxj, layout, depth+1, counter,  \
		map_in_prog ) == 1)
			return 1;
	else if (make_maze( i, j+1, maxi, maxj, layout, depth+1, counter,  \
		map_in_prog ) == 1)
			return 1;
	else if (make_maze( i, j-1, maxi, maxj, layout, depth+1, counter,  \
		map_in_prog) == 1)
			return 1;
	//once the program has traversed all the conditionals and there is no 
	//success, we return 0 to signal the program to keep creating maze-like
	//behavior
	return 0;
}


int retrieve(int i, int j, int maxi, int maxj, char ** layout, 
	map< pair<int,int>, bool> & in_map)
{
	if (i < 0 || j <0 || i == maxi || j == maxj || layout[i][j] == '0')
		return 0; //if we have exceeded defined bounds of the matrix, return
		//to avoid segfaulting
	pair<int,int> local_pair = make_pair(i,j);
	if ( in_map[local_pair] == true)
		return 0; /*if we have visited this locaiton before,
		avoid redundant traversal... this redundant traversal
		will actually cycle into an infinite recursion. We don't want that*/
	else in_map[local_pair] = true;  // make sure to mark location as visited


	if ( layout[i][j] == '9') // we have reached our objective. signal success
		return 1;
		
		
	if (retrieve( i+1, j, maxi, maxj, layout, in_map) == 1){
		layout[i][j] = '+'; //marking the location of traversed path to objective
		return 1;	
	}
	else if (retrieve( i - 1, j, maxi, maxj, layout, in_map) == 1){
		layout[i][j] = '+';
		return 1;
		}
	else if (retrieve( i, j-1, maxi, maxj, layout, in_map) == 1){
		layout[i][j] = '+';
		return 1;
	}
	else if (retrieve( i, j+1, maxi, maxj, layout, in_map) == 1){
		layout[i][j] = '+';
		return 1;
	}
	else{
		layout[i][j] = '^';
		return 0; //else, no success
	}

}



char ** generate_maze( int row, int col ){
	bool flag = false;
	char ** arr = new char*[row];
	for (int i = 0; i < row; ++i){
		char * local_arr = new char[col];
		for (int j = 0; j < col; ++j){
			int in_num = rand();
			if (in_num%37==0&& !flag){ //pick a number to make 9 generation 
									  // more difficult
				local_arr[j] = '9';
				flag = true;
			}


			else local_arr[j] = (char)(in_num%2 + 48); //is it a wall or a path?
		}
		arr[i] = local_arr;
	
	}
	if (!flag)
		arr[row-1][col-1] = '9'; //if 9 isnt in the maze, insert in last position
	return arr;
}
	



int main(){
	int presence;
	int maxi, maxj;
	cout << "now enter the bounds" << endl;
	cin >> maxi >> maxj;
	srand( time(NULL) ); // seed the pseduorandom number generator with system time
	// the way the generator works is pretty interesting, definitely worth reading up
	//there was a lot of research in the early days of computing to find a robust 
	// random number generator that generated seemingly random integers.

	map< pair<int,int>, bool> maze_checker; //used for making maze more maze-like
	map< pair<int,int>, bool> inmap; // used for maze during traversal
		
	char ** layout = generate_maze( maxi, maxj );
	int maze_i = 0, maze_j = 0;
	int depth = 0;

//this displays the map before increasing the "maze-iness"
	for (int i = 0; i < maxi; ++i){
		for (int j = 0; j < maxj; ++j){
			maze_checker[make_pair(i, j)] = false; // init all values to false
			cout << " | " << layout[i][j] ;
		}
		cout << endl;
	}
	cout <<"\n\n\n\n" << endl;
	//after "maze-iness"
	make_maze( maze_i, maze_j, maxi, maxj, layout, depth, 0, maze_checker);
	for (int i = 0; i < maxi; ++i){
		for (int j = 0; j < maxj; ++j){
			inmap[make_pair(i, j)] = false; // init all values to false
			cout << " | " << layout[i][j] ;
		}
		cout << endl;
	}


	int output = retrieve( maze_i, maze_j, maxi, maxj, layout, inmap);
	cout << output << endl;
	if (output || !output){
		for (int i = 0; i < maxi; ++i){
			for (int j = 0; j < maxj; ++j){
				cout << " | " << layout[i][j] ;
			}
			cout << endl;
		}
	}


	for (int k = 0; k < maxi; ++k)
		delete[] layout[k];
	delete[] layout;
	return 0;
}
