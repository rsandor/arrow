/*
 * Emitters are used to generate semi-controlled bursts of particles used to model
 * things like weponry and debris in the game world.
 */

#pragma once

#include <list>
#include <math.h>
#include <GLUT/glut.h>

/**
 * Particle structure.
 */
class Particle {
	public:
		Particle(int);
		
		void update();
		void setPosition(double, double);
		void setVelocity(double, double);
		
		double getX();
		double getY();
		int getLife();
		
		bool isDead();
	private:
		double x;
		double y;
		double dx;
		double dy;
		int life;
};

/**
 * Sets a point from which particles are emitted.
 */
class Emitter {
  public: 
    Emitter();

    void setPosition(double, double);
    void setRotation(double);
    void setVelocity(double);
    void setSpread(double);
    void setLifespan(int);
    void setMaxParticles(int);
		void setDelay(int);

		void on();
		void off();

		void update();
		void render();

  protected:
		void emit();

  private:
		std::list <Particle*> particles;
	
    double x;
    double y;
  
		int delay; 					// Delay steps between emissions
		int timer; 					// Current delay timer value

    double rotation;		// Rotation in degrees
		double spread;			// Spread in degrees
    double velocity;
    
		bool emitting;

    int max_particles;
    int lifespan;
};
