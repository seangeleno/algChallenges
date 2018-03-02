#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct box_container{
	int i;
	int j;
	int dimensions;
} box_container;

typedef struct{
	int x, y;
	char* visual;
//	char* (*display)(void);
} box;
void init_box(box*, struct box_container, const char );


typedef struct{
	box *** blocks;
	int dimensions;

} map;

char getrandchar(const char* str, const int state){
	switch(rand()%3){
	case 0:
		if (!state || str[state-1]!='|')
			return '|';
	case 1:
		return ' ';
	case 2:
		return '_';
	default:
		break;
	}
}



void display(map* game_map){
	for (int i = 0; i < game_map->dimensions; ++i){
		for (int j = 0; j < game_map->dimensions; ++j){
			printf("%s",game_map->blocks[i][j]->visual);
		}
		printf("\n");
	}
}




//dynamic programming: recursively traverse from start of maze to find end, looking at box strings and how the match up(i-1, j) (i+1, j), (i, j+1), (i, j-1);
// if no path, insert space character to create path

void init_box(box* _box, struct box_container container, const char previous){
	
	_box->visual = (char*)malloc(sizeof(char)*3);
	int count = 0;
	if (previous == '|'){
		_box->visual[0] = ' ';
		++count;
	}
	
	if (container.i == 0){
			_box->visual[0] = '_';
			_box->visual[1] = '_';
			_box->visual[2] = 0;
	}
	else if (container.i == 1 && container.j == 0){
			_box->visual[0] = '|';
			_box->visual[1] = getrandchar(_box->visual, 1);
			_box->visual[2] = 0;
	}
	else if (container.i == 1 && container.j == container.dimensions-1){
			_box->visual[0] = getrandchar(_box->visual, 0);
			_box->visual[1] = '|';
			_box->visual[2] = 0;
	}
	else if(container.j == 0 && container.i == container.dimensions-1){
		_box->visual[0] = '|';
		_box->visual[1] = '_';
		_box->visual[2] = 0;
	}
	else if(container.j == 0){		
			_box->visual[0] = '|';
			_box->visual[1] =  getrandchar(_box->visual, 1);
			_box->visual[2] = 0;
	}
	else if (container.j == container.dimensions-1 && container.i == container.dimensions-1){
		_box->visual[0] = '_';
		_box->visual[1] = '|';
		_box->visual[2] = 0;
	}
	else if (container.j == 0 && container.i == container.dimensions-1){
		_box->visual[0] = '|';
		_box->visual[1] = '_';
		_box->visual[2] = 0;
	}
	else if (container.i == container.dimensions-1){
		char back = getrandchar(_box->visual, 0);
		_box->visual[0] = back;
		if (back == ' ')
			_box->visual[0] = '_';
		if (back != '_')
			_box->visual[1] = '_';
		else
			_box->visual[1] = '|';
		_box->visual[2] = 0;
	}
	else if (container.j == container.dimensions-1 ){
		_box->visual[0] = getrandchar(_box->visual, 0);
		_box->visual[1] = '|';
		_box->visual[2] = 0;
	}
	else{
		do{
			_box->visual[count] = getrandchar(_box->visual, count);
			++count;	
		}while(count < 2);
		_box->visual[2] = 0;
	}	
}

void create_map(map* game_map, const int _dimensions ){
	game_map->blocks = (box***)malloc(sizeof(box**)*_dimensions);

	game_map->dimensions = _dimensions;
	for (int i = 0; i < _dimensions; ++i){
		game_map->blocks[i] = (box**)malloc(sizeof(box*)*_dimensions);
		
		char char_buffer = 'l';
		#pragma GCC ivdep
		for (int j = 0; j < _dimensions; ++j){
			game_map->blocks[i][j] = (box*)malloc(sizeof(box));
			struct box_container to_pass;
			to_pass.i = i; to_pass.j = j; to_pass.dimensions = _dimensions;
			
			init_box(game_map->blocks[i][j], to_pass, char_buffer);
			char_buffer = game_map->blocks[i][j]->visual[1];
		}
	}
}




void destroy_map(map* game_map){
	for (int i = 0; i < game_map->dimensions; ++i){
		#pragma GCC ivdep
		for (int j = 0; j < game_map->dimensions; ++j){
			free(game_map->blocks[i][j]->visual);
			free(game_map->blocks[i][j]);
		}
	}
}




































int main(int argc, char ** argv){
	if (argc != 2){
		fprintf(stderr,"Not enough inputs\n");
		return EXIT_FAILURE;
	}	

	srand(time(NULL));
	int size = atoi(argv[1]);
	map* game_map = (map*)malloc(sizeof(map));
	create_map(&game_map, size);
	display(&game_map);
	destroy_map(&game_map);
	free(game_map);


	return EXIT_SUCCESS;
}
