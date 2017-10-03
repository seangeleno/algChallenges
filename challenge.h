#pragma once

#include <stdint.h>
#include <stdlib.h>

typedef struct {
	int16_t x;
	int16_t y;
} point;

typedef struct {
	uint8_t	hero;
	uint8_t	villain;
	point		position;
} player;

// Task: Simulate the game as a series of atomic steps
// whereby each player moves up to the distance `step`
// (pythagorean distance) to achieve their goal such
// that each player acts in their own best interest
// over `time` number of steps through the simulation
player *simulate (const player *p, size_t pn, \
		const point *bounds, size_t bn, \
		uint8_t step, size_t time);

// Task: Find an optimal arrangement of players such
// that the players' goals are simultaneously achieved
// as best possible
player *solve (const player *p, size_t pn, const point *bounds, size_t bn);


