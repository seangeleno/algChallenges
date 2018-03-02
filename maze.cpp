#include <iostream>
#include <map>
#include <utility>
#include <time.h>
using namespace std;

int  make_maze(int i, int j, int maxi, int maxj, int ** layout, int depth, int counter, map< pair<int,int>, bool> & map_in_prog ){
	if (i<0 || j < 0 || i == maxi || j == maxj )
		return 0;
	if ( map_in_prog[make_pair(i,j)] == true)
		return 0;
	else map_in_prog[make_pair(i,j)] = true;

	

		
		
		
		
		
		if (layout[i][j] == 9)
			return 1;

		else if ( (depth < 3|| ++counter > 3) && layout[i][j] == 0){
			layout[i][j] = 1;
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
		else if (make_maze( i + 1, j, maxi, maxj, layout, depth+1, counter, map_in_prog ) == 1)
			return 1;

		else if (make_maze( i-1, j, maxi, maxj, layout, depth+1, counter, map_in_prog ) == 1)
			return 1;
		else if (make_maze( i, j+1, maxi, maxj, layout, depth+1, counter, map_in_prog ) == 1)
			return 1;
		else if (make_maze( i, j-1, maxi, maxj, layout, depth+1, counter, map_in_prog) == 1)
			return 1;
		return 0;
}


int check(int i, int j, int maxi, int maxj, int ** layout, map< pair<int,int>, bool> & in_map){
	if (i < 0 || j <0 || i == maxi || j == maxj || layout[i][j] == 0)
		return 0;
	if ( in_map[make_pair(i,j)] == true)
		return 0;
	else in_map[make_pair(i,j)] = true;
	if ( layout[i][j] == 9)
		return 1;
		
		
		
		
		
	if (check( i+1, j, maxi, maxj, layout, in_map) == 1){
		layout[i][j] = 5;
		return 1;	
	}
	else if (check( i - 1, j, maxi, maxj, layout, in_map) == 1){
		layout[i][j] = 5;
		return 1;
		}
	else if (check( i, j-1, maxi, maxj, layout, in_map) == 1){
		layout[i][j] = 5;
		return 1;
	}
	else if (check( i, j+1, maxi, maxj, layout, in_map) == 1){
		layout[i][j] = 5;
		return 1;
	}
	else
		return 0;

}



int ** generate_maze( int row, int col ){
	bool flag = false;
	int ** arr = new int*[row];
	for (int i = 0; i < row; ++i){
		int * local_arr = new int[col];
		for (int j = 0; j < col; ++j){
			int in_num = rand();
			if (in_num%37==0&& !flag){
				local_arr[j] = 9;
				flag = true;
			}
			else local_arr[j] = in_num%2;
		}
		arr[i] = local_arr;
	
	}
	if (!flag)
		arr[row-1][col-1] = 9;
	return arr;







}
	



int main(){
	int presence;
	int maxi, maxj;
	cout << "now enter the bounds" << endl;
	cin >> maxi >> maxj;
	srand( time(NULL) );

	map< pair<int,int>, bool> maze_checker;
	map< pair<int,int>, bool> inmap;
		
	int ** layout = generate_maze( maxi, maxj );
	int maze_i = 0, maze_j = 0;
	int depth = 0;
//this displays the map before increasing the "maze-iness"
	for (int i = 0; i < maxi; ++i){
		for (int j = 0; j < maxj; ++j){
			maze_checker[make_pair(i, j)] = false;
			cout << " | " << layout[i][j] ;
		}
		cout << endl;
	}
	cout <<"\n\n\n\n" << endl;
	//after "maze-iness"
	make_maze( maze_i, maze_j, maxi, maxj, layout, depth, 0, maze_checker);
	for (int i = 0; i < maxi; ++i){
		for (int j = 0; j < maxj; ++j){
			inmap[make_pair(i, j)] = false;
			cout << " | " << layout[i][j] ;
		}
		cout << endl;
	}
	int output = check( maze_i, maze_j, maxi, maxj, layout, inmap);
	cout << output << endl;
	if (output){
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
