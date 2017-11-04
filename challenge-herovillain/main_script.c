#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "challenge.h"
#include "challenge_wrappers.h"

uint8_t position_check(player*, point_w_flg**, size_t);
player* players_init( const size_t pn, point_w_flg ** game_map, const size_t bn );
void player_check( player*, const size_t, const uint8_t, const size_t );
point_w_flg** game_map_init( const size_t bn );










int main_script( void ){
	player * players;
	point_w_flg ** game_map;
	size_t pn, bn, iterations;
	uint8_t step;
	//every array is pass by reference in c


//READ IN PARAMETERS 
	uint16_t seed;
    scanf("%hhu", &seed);
    srand(seed);

    printf(" ENTER  NUM PLAYERS, SIZE MAP, NUM STEPS, TOTAL TIME\n");
    scanf("%zu", &pn);
    scanf("%zu", &bn);
    scanf("%hhu", &step);
    scanf("%zu", &iterations );


/* GAME MAP INITIALIZERS */
	game_map = game_map_init( bn );
/* PLAYER INITIZLIERS, LATER TO CONTAIN DEEP COPY OF ORIGINAL ARRAY*/
	players = players_init( pn, game_map, bn );


	_simulate( players, pn, game_map,bn, step, iterations);
	for (size_t i = 0 ; i < pn; i++){
		printf("PLAYER %zu AT (%hd, %hd), hero = %hhu vill = %hhu\n", i, players[i].position.x, players[i].position.y, players[i].hero, players[i].villain);
	}
	printf("\n\n\n");



/*DEALLOCATE MEM*/
	free(players);
	for (int i = 0; i < bn; i++){
		free(game_map[i]);
	}
	free(game_map);


	printf("sim completed yeet\n\n");
	return EXIT_SUCCESS;
}





point_w_flg** game_map_init( const size_t bn ){
	point_w_flg ** game_map = (point_w_flg**)malloc( bn * sizeof(point_w_flg*));
	for ( size_t i = 0; i < bn; i++)
	{
		game_map[ i ] = (point_w_flg*) malloc(bn*sizeof(point_w_flg));
	}
	for ( size_t i = 0; i < bn; i++){
		for (size_t j = 0; j < bn; j++){

			game_map[i][j].coord.x = (0 - (bn/2))+ i;
			game_map[i][j].coord.y = (0 - (bn/2)) + j;
			game_map[i][j].occupied = 0;
		}
	}
	return game_map;

}


player* players_init( const size_t pn, point_w_flg ** game_map,
	const size_t bn){
	//Init plaers. position check makes sure another not assigned at randomly generated assignmnets
	player * players = (player*)malloc( pn * sizeof(player));
	for (size_t i =0; i < pn; i++){
		position_check(&players[i], game_map, bn);
		player_check(&players[i], pn, 0, i);
		player_check(&players[i], pn, 1, i);
	}
	for (size_t i = 0 ; i < pn; i++){
		printf("PLAYER %zu AT (%hd, %hd), hero = %hhu vill = %hhu\n", i, players[i].position.x, players[i].position.y, players[i].hero, players[i].villain);
	}
	printf("\n\n\n");
	return players;
}


void player_check( player* assign_to_me, const size_t pn,
	const  uint8_t h_or_v, const size_t curr_loc){

	while(1){
		uint8_t to_assign = (uint8_t) (rand() % pn);
		if (!(to_assign == curr_loc)){
			if (!h_or_v){
				assign_to_me->hero = to_assign;
				return;
			}
		  else if (assign_to_me->hero != to_assign){
				assign_to_me->villain = to_assign;
				return;
			}
		}
	}
}


//check for occupancy
uint8_t position_check(player* assign_to_me, point_w_flg ** game_map, size_t bounds ){
	

	while( 1 ){
		int16_t index_i = (int16_t) (rand() % bounds);
		int16_t index_j = (int16_t) (rand() % bounds);
		if (!game_map[index_i][index_j].occupied){
			assign_to_me->position.x = index_i - bounds / 2;
			assign_to_me->position.y = index_j - bounds / 2;
			(game_map[index_i][index_j]).occupied++;
			return 1;
		}
	}
}
