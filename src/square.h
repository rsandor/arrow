/*
 * Basic enemy type: the square.
 */

#include "entity.h"
#include "effects.h"
#pragma once

class Square: public Entity {
	public:
		Square();
		void update(double, double);
		void render();
		bool checkHit(double, double);
		bool isDead();
		
	private:
		double d_wiggle;
		double wiggle;
		double max_wiggle;
		
		// Just playing with this for now
		int health;
};

class SquareExplosion: public Effect {
  public: 
    SquareExplosion(Square *square);
    void render();
  private:
    double x;
    double y;
};

