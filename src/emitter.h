/*
 * Emitters are used to generate semi-controlled bursts of particles used to model
 * things like weponry and debris in the game world.
 */

#pragma once

#include <list>
#include <math.h>
#include <GLUT/glut.h>
#include "square.h"
#include "effects.h"

/**
 * Individual particle instance.
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
 * Explosion effect for when particles hit an enemy.
 */
class ParticleHit: public Effect {
public:
  ParticleHit(double, double);
  void render();
private:
  double x;
  double y;
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
  void setBurst(int);

	void on();
	void off();

	void update();
	void render();
	
  int size();
	
	// Ewww, need to find a good way to deal with this
	void checkHits(Square *);

protected:
	void emit();

private:
	std::list <Particle*> particles;

  double x;
  double y;

	int delay; 					// Delay steps between emissions
	int timer; 					// Current delay timer value
  int burst;          // Number of particles to release in a burst

  double rotation;		// Rotation in degrees
	double spread;			// Spread in degrees
  double velocity;
  
	bool emitting;

  int max_particles;
  int lifespan;
};
