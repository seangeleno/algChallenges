#include "challenge.h"
#include <math.h>

double update_pos( player, const uint16_t, const uint16_t );


point get_loc( player my_loc ){
    return my_loc.position;
}

double update_alignment( player* my_player, player * players_original, \
    uint8_t step, point * map ){
    player local_hero = players_original[ my_player.hero ];
    player local_villain = players_original[ my_player.villain ];
    point align1 = get_loc( local_villain );
    point align2 = get_loc( local_hero );
    point offset_vill = { align1.x - my_player.position.x, align1.y- my_player.position.y };
    point offset_hero = { align2.x - my_player.position.x, align2.y - my_player.position.y };
    
    double score = 0.0;
}

double update_pos( player my_player, uint16_t update_X, uint16_t update_Y )
{
   my_player.position.x+=update_X;
   my_player.position.y+=update_Y; 
}

double update_score( player my_player, point offset_hero, point offset_vill ){
    
    point player_pos = my_player.position;

    int16_t diff_x_hero = player_pos.x - offset_hero.x;
    int16_t diff_y_hero = player_pos.y - offset_hero.y;  
    double pythag_2_hero = (diff_x_hero, * diff_x_hero) + (diff_y_hero * diff_y_hero)
    double distance_hero = sqrt(pythag_2_hero);


    int16_t diff_x_vill = player_pos.x - offset_vill.x;
    int16_t diff_y_vill = player_pos.y - offset_vill.y;
    double pythag_2_vill = (diff_x_vill * diff_x_vill) + (diff_y_vill * diff_y_vill);
    double distance_vill = sqrt(pythag_2_vill);

    int16_t diff_vill_hero_x = offset_hero.x - offset_vill.x;
    int16_t diff_vill_hero_y = offset_hero.y - offset_vill.y;
    double pythag_2_hero_vill = (diff_vill_hero_x * diff_vill_hero_x) + (diff_vill_hero_y * diff_vill_hero_y);
    double distance_hero_vill = sqrt(pythag_2_hero_vill);

    //trig to find arctan of players pos relative to the line 
    double hypotenus;
    double adj;
    double opp;

    double angle; 
    if ((distance_hero_vill > distance_hero) && 
        (distance_hero_vill > distance_vill)){
        hypotenus = distance_hero_vill;
        adj = distance_hero;
        opp = distance_vill;
        angle = acos(adj / hypotenus);
    }
    else if ((distance_hero > distance_hero_vill) && 
        (distance_hero > distance_vill)){
            hypotenus = distance_hero; 
            adj = distance_vill;
            opp = distance_hero_vill;
            angle = atan(opp / adj);
        } 
    else{
        hypotenus = distance_vill;
        adj = distance_hero_vill;
        opp = distance_hero;
        angle = asin(opp / hypotenus);
    }
    double score = (distance_hero + distance_vill) / angle;  //find a way to normalize ratio
    return score;
}

