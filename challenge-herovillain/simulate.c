//simulate
#include "challenge.h"
#include "challenge_wrappers.h"
#include <stdio.h>
uint8_t _simulate( player * players, const size_t pn, point_w_flg ** game_map, const size_t bn,
	const uint8_t step, const size_t time ){

	player* players_og = (player*)malloc(pn*sizeof(player));
	for( size_t J = 0; J < time; J++){
		char player_file[25];
		snprintf(player_file, sizeof(player_file), "player-data%zu.txt", J);
		FILE * file_p = fopen(player_file,"w");
		printf("\r\n\n\n\n\n\nNEW CLOCK CYCLE: TICK %zu\n", J);
		for (size_t i = 0; i < pn; i++){
			players_og[ i ] = players[i];


			fprintf(file_p, "%zu, %hd, %hd \r\n", i, players[i].position.x, players[i].position.y);
		}
		fclose(file_p);



		for ( size_t i = 0; i < pn; i++ ){
			update_alignment( &players[ i ], players_og[ players[i].hero], \ 
			 players_og[players[i].villain], step, game_map, bn, i);



			/*printf("player %zu is at loc (%d, %d)\r\n" \
				"hero at (%d,%d), vill at (%d,%d)\r\n\n", \
				i, players[i].position.x, players[i].position.y,	
					players_og[	players[i].hero ].position.x,
					players_og[ players[i].hero ].position.y,
					players_og[ players[i].villain ].position.x,
					players_og[ players[i].villain ].position.y);*/
		}
	}
	free(players_og);
	return 1;
}
/*player * simulate( const player* p, size_t pn,
	const point *bounds, size_t bn,
	uint8_t step, size_t time){
	player* players = (player*)malloc(pn*sizeof(player));
	for ( size_t i = 0; i < pn; i++){
		players[i] = p[i];
	}
} 

player * solve( const player * p, size_t pn, 
const point * bounds, size_t bn) {
*/

//like simulate, except repeat until all scores 
//are below a threshold value of score
