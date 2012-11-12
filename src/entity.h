/*
 * Entities are renderable game objects that have a position, direction, and a 
 * velocity. Examples include the player's ship and various enemies.
 */

#pragma once

class Entity {
	public:
		Entity();
		
		void update();
		void render();
		
		void setPosition(double, double);
		void setVelocity(double);
		void setRotation(double);
		void addRotation(double);
		
		double getX();
		double getY();
		double getRotation();
		double getVelocity();

	protected:
		void normalizeRotation();
		double x;
		double y;
		double rotation;
		double velocity;
};

