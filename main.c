#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <string.h>
#include "challenge.h"
uint8_t position_check(player*, point**, size_t);
int main( int argc, char ** argv){
	player * players;
	point ** game_map;
	//every array is pass by reference in c



    srand( time(NULL));
	for (int i = 0; i < argc; i++){
		printf("Command line arg %2d: %s\n", i, argv[i]);
	}
	if ( argc != 5){
		fprintf(stderr, "wrong num of command line args. require 4");
		return EXIT_FAILURE;
	}
	printf("\n\n");
	size_t pn = atoi(argv[1]);
	size_t bn = atoi(argv[2]);
	uint8_t step = atoi(argv[3]);
	size_t time = atoi(argv[4]);
	game_map = (point_w_flg**)malloc( bn * sizeof(point_w_flg*));
	for ( int i = 0; i < bn; i++)
	{
		game_map[ i ] = (point_w_flg*) malloc(bn*sizeof(point_w_flg))
	}
	for ( int i = 0; i < bn; i++){
		for (int j = 0; j < bn; j++){

			game_map[i][j].coord.x = i;
			game_map[i][j].coord.y = j;
			game_map[i][j].occupied = 0;
		}
	}

	players = (player*)malloc( pn * sizeof(player));
	for (int i =0; i < pn; i++){
		position_check(&players[i], game_map, bn);
		players[i].hero = (uint8_t) (rand() % pn);
		players[i].villain = (uint8_t) (rand() % pn);
	}

	while (1){
		if (!simulate( players, game_map, step, time)){
			break;
		}
	}

	free(players);
	for (int i = 0; i < bn; i++){
		free(game_map[i]);
	}
	free(game_map);



	return EXIT_SUCCESS;
}

uint8_t position_check(player* assign_to_me, point ** game_map, size_t bounds ){
	point position_buffer;


	while( 1 ){
		position_buffer.x = (int16_t) (rand() % bounds);
		position_buffer.y = (int16_t) (rand() % bounds);
		if (!game_map[position_buffer.x][position_buffer.y].occupied){

			assign_to_me->position = position_buffer;
			(game_map[position_buffer.x][position_buffer.y]).occupied++;
			return 1;
		}
	}
}
