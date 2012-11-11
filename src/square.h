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
	private:
		double d_wiggle;
		double wiggle;
		double max_wiggle;
};
