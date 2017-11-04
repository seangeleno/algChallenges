#include "challenge.h"
#include "challenge_wrappers.h"
#include <math.h>

#define PI 3.1415926535


double update_pos( player *, const uint16_t, const uint16_t );

double update_score( player * my_player, point offset_hero, point offset_vill, 
		point_w_flg**, const size_t bn);

uint8_t boundary_check( player* my_player, point_w_flg ** map, const size_t bn,
	int16_t * move_x, int16_t * move_y );
uint8_t occupency_check( player*, point_w_flg **, const size_t, int16_t*, int16_t*);
double update_alignment( player* my_player, player local_hero, player local_villain, \
	uint8_t step, point_w_flg ** map, const size_t bn, const size_t player_id );









point get_loc( player my_loc ){
	//streamline location fetch
	return my_loc.position;
}

double update_alignment( player* my_player, player local_hero, player local_villain, \
	uint8_t step, point_w_flg ** map, const size_t bn, const size_t player_id){
	//
	uint8_t count = 0;
	double score;
	while( count < step ){
		point align1 = get_loc( local_villain );
		point align2 = get_loc( local_hero );
		point offset_vill = { my_player->position.x - align1.x, my_player->position.y - align1.y };
		point offset_hero = { my_player->position.x - align2.x, my_player->position.y - align2.y };
		score = update_score( my_player, offset_hero, offset_vill, map, bn );
		if (score > 140 || score < 30 ) count*=2;
		if (score > 150 || score < 20 ) break;
		count++;
	}
	if ( score > 150 || score < 20 ){
		printf("\n***************************************************"\
			"\nplayer %zu is approaching its LINE, angle at %lf\n"\
			"***************************************************\n",player_id, score );
	}

	return score;
}




double update_score( player * my_player, point offset_hero, point offset_vill,
	point_w_flg ** map, const size_t bn){
	
	point player_pos = my_player->position;

	//HERO VECTOR
	int16_t diff_x_hero = offset_hero.x;
	int16_t diff_y_hero = offset_hero.y;
	int16_t diff_x_h_move, diff_y_h_move;
	int16_t diff_x_v_move, diff_y_v_move;
	if (diff_x_hero > 0){
		diff_x_h_move = -1;
	}  else{
		diff_x_h_move = 1;
	} 
	if (diff_y_hero > 0){
		diff_y_h_move = -1;
	} else{
		diff_y_h_move = 1;
	}
	double pythag_2_hero = (diff_x_hero * diff_x_hero) + (diff_y_hero * diff_y_hero);
	double distance_hero = sqrt(pythag_2_hero); //MAG OF HERO DISTANCE VECTOR
	//END HERO VECTOR


	//VILLAIN VECTOR
	int16_t diff_x_vill = offset_vill.x;
	int16_t diff_y_vill = offset_vill.y;

	if (diff_x_vill > 0){
		diff_x_v_move = -1;
	}  else{
		diff_x_v_move = 1;
	}
	if (diff_y_vill > 0){
		diff_y_v_move = -1;
	}  else{
		diff_y_v_move = 1;
	}
	double pythag_2_vill = (diff_x_vill * diff_x_vill) + (diff_y_vill * diff_y_vill);
	double distance_vill = sqrt(pythag_2_vill);//MAG OF VILLAIN VECTOR

	int16_t diff_vill_hero_x = offset_hero.x - offset_vill.x;
	int16_t diff_vill_hero_y = offset_hero.y - offset_vill.y;
	//END VILLAIN VECTOR

	
	//VECTOR BETWEEN HERO AND VILLAIN
	double pythag_2_hero_vill = (diff_vill_hero_x * diff_vill_hero_x) + (diff_vill_hero_y * diff_vill_hero_y);
	double distance_hero_vill = sqrt(pythag_2_hero_vill);//MAGNITUDE

	

	//trig to find arctan of players pos relative to the line 
	//printf(" magplayer_hero: %lf\n mag player_villain: %lf\r\nmag hero_vill: %lf\r\n", distance_hero, distance_vill, distance_hero_vill);
	//law of sines lenA/ sin(a) == lenB/ sin(b) == lenX / sin(C)
	//law of cosines : C^2 == A^2 + B^2 - 2ab(c)
	double A,B,C; 
	uint8_t case_;
	if ((distance_hero > distance_vill) && (distance_hero > distance_hero_vill)){
		C = distance_hero;
		B = distance_vill;
		A = distance_hero_vill;
		case_ = 0;
	}
	else if ((distance_vill > distance_hero)&&(distance_vill>distance_hero_vill)){
		C = distance_vill;
		B = distance_hero;
		A = distance_hero_vill;
		case_ = 1;
	}
	else{
		C = distance_hero_vill;
		B = distance_hero;
		A = distance_vill;
		case_ = 2;
	}
	double cos_c = (((A * A) + ( B  * B)
	 - (C * C))
	/ (2*(A * B)));
	double angle;
	switch( case_ ){
		case 0:
			angle = asin((A * sin(acos(cos_c)) )/  C);
			break;
		case 1:
			angle = asin((A * sin(acos(cos_c)))/ C);
			break;
		case 2:
			angle = acos(cos_c);
			break;
		default:
			break;
	};


	angle = angle * 180.0/PI;
	//printf("angle opp the line between hero and villain:  %lf \r\n", angle);

	//CHECK FOR COLLISION/OVERSTEPPING   
	boundary_check(my_player, map, bn, &diff_x_h_move, &diff_y_h_move);
	boundary_check(my_player, map, bn, &diff_x_v_move, &diff_y_v_move);
	occupency_check(my_player, map, bn, &diff_x_h_move, &diff_y_h_move);
	occupency_check(my_player, map, bn, &diff_x_v_move, &diff_y_v_move);

	//USED FOR DECREMENTING OCCUPANY FLAG
	uint16_t orig_index_x = (*my_player).position.x + lround(bn/2) ;
	uint16_t orig_index_y = (*my_player).position.y + lround(bn/2) ;

	//UPDATE LOCATION
	if (diff_x_hero > diff_x_vill &&(my_player->position.x != offset_hero.x)){
		if (distance_hero > 10){
			my_player->position.x+= diff_x_h_move;			
		}
	}  else if ( my_player->position.x != offset_vill.x){
		if (distance_vill > 10){
		my_player->position.x+=diff_x_v_move;
		}		
	}//X
	if (diff_y_hero > diff_y_vill && (my_player->position.y != offset_hero.y)){
		my_player->position.y+=diff_y_h_move;
	}  else if (my_player->position.y != offset_vill.y){
		my_player->position.y+=diff_y_v_move;
	}//Y



	//DECREMENT OCCUPANCY
	map[orig_index_x][orig_index_y].occupied--;
	map[(*my_player).position.x + lround(bn/2) ] \ 
		[(*my_player).position.y + lround(bn/2) ].occupied++;//INC
return angle   ;
}

























uint8_t occupency_check( player* my_player, point_w_flg ** map, const size_t bn, int16_t * move_x, int16_t * move_y ){
	//CHECK FOR MAP POINTS BEING OCCUPIED
	uint8_t MODFLG = 0;

	if ( map[ (*my_player).position.x + lround(bn/2) + *move_x ] 
		[ (*my_player).position.y + lround(bn/2) + *move_y ].occupied ){
		*move_x = -*move_x;
		*move_y = 0;
		MODFLG++;
	}
	return MODFLG;
}


uint8_t boundary_check( player* my_player, point_w_flg ** map, const size_t bn,  \
	int16_t * move_x, int16_t * move_y ){
	//test leftmost x boundary, right most,  bottom y, top y
	// return MODFLG to signal change to passed in vals;
	uint8_t MODFLG = 0;
	if ((map[0][0].coord.x == (*my_player).position.x)
		&& (*move_x == -1)) {
			*move_x = 1;
			MODFLG++;
	}
	else if (( map[bn-1][bn-1].coord.x == (*my_player).position.x)
		&& (*move_x == 1)){
			*move_x = -1;
			MODFLG++;
	}
	if ((map[0][0].coord.y == (*my_player).position.y)
		&& (*move_y == -1)){
			*move_y = 1;
			MODFLG++;
	}
	else if ((map[bn-1][bn-1].coord.y == (*my_player).position.y) 
		&& (*move_y == 1)){
			*move_y = -1;
			MODFLG++;
	}

	return MODFLG;
}
