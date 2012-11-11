/*
 * Basic enemy type: the square.
 */

#include "entity.h"
#pragma once

class Square: public Entity {
	public:
		Square();
		void update(double, double);
		void render();
		bool checkHit(double, double);
		
	private:
		double d_wiggle;
		double wiggle;
		double max_wiggle;
		
		// Just playing with this for now
		int health;
};
