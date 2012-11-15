/*
 * Models the player entity, or "Arrow", in the game world.
 */

#pragma once
#include "entity.h"

class Player: public Entity {	
	public:
		Player();
		void rotateLeft();
		void rotateRight();
		void moveForward();
		void moveBackward();
		void stop();
		void render();
	
	private:
		double max_velocity;
		double max_rotation;
		double scale;
};