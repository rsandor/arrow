/*
 * Utility macros for the game.
 */

#pragma once

#include <math.h>
#include <time.h>
#include <stdlib.h>

// Random floating point uniform between 0 and 1
#define uniform()		( (double)rand() / (double)RAND_MAX )

// Random integer between 0 and N
#define randint(N)	( (int)(uniform() * N) )

// Convert degrees to radians
#define deg2rad(D) 	((M_PI * D) / 180.0 + M_PI_2);

// Screen width and height
extern int screen_width;
extern int screen_height;

