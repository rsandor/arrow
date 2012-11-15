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

#define normDeg(D)  ((D) >= 360.0 ? (D) - 360.0 : ((D) < 0 ? (D) + 360.0 : (D)))



// Screen width and height
extern int screen_width;
extern int screen_height;

// Layers
#define setLayer(L) (_currentLayer = (L))
#define vertex(X, Y) (glVertex3f((X), (Y), _currentLayer))

#define LAYER_BACKGROUND  0.0

#define LAYER_GRID_MINOR  0.1
#define LAYER_GRID_MAJOR  0.2

#define LAYER_PLAYER_BG   50.0
#define LAYER_PLAYER_FG   50.1
#define LAYER_ENEMIES     50.2

#define LAYER_PARTICLES   90.0
#define LAYER_EFFECTS     90.1

extern double _currentLayer;

// FPS Calculation
void calcFPS();
double getFPS();