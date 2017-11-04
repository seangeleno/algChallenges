//challenge_wrappers.h
#pragma once
#include "challenge.h"
#include <GL/glew.h>
typedef struct {
	point coord;
	uint8_t occupied;
}point_w_flg;

int main_script( void );
uint8_t _simulate( player * players, const size_t pn, point_w_flg ** game_map, const size_t bn,
  const uint8_t step, const size_t time );