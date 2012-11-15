#include <iostream>
#include "emitter.h"
#include "util.h"

using namespace std;

/**
 * Particle implmentation
 */

Particle::Particle(int startLife) {
	x = 0.0;
	y = 0.0;
	dx = 0.0;
	dy = 0.0;
	life = startLife;
}

void Particle::setPosition(double newX, double newY) {
	x = newX;
	y = newY;
}

void Particle::setVelocity(double newDX, double newDY) {
	dx = newDX;
	dy = newDY;
}

void Particle::update() {
	x += dx;
	y += dy;
	life--;
}

bool Particle::isDead() { return life <= 0; }
double Particle::getX() { return x; }
double Particle::getY() { return y; }
int Particle::getLife() { return life; }

/*
 * Emitter Implementation
 */
Emitter::Emitter() {
  x = 0;
  y = 0;
  rotation = 0.0;
  velocity = 1.0;
  spread = 1.0;
  max_particles = 100;
  lifespan = 1000;
	emitting = false;
  burst = 1;
}

void Emitter::setPosition(double newX, double newY) {
  x = newX;
  y = newY;
}

void Emitter::setRotation(double r) {
  rotation = r;
}

void Emitter::setVelocity(double v) {
  velocity = v;
}

void Emitter::setSpread(double s) {
  spread = s;
}

void Emitter::setLifespan(int l) {
  lifespan = l;
}

void Emitter::setMaxParticles(int m) {
  max_particles = m;
}

void Emitter::setDelay(int newDelay) {
	delay = newDelay;
	timer = delay;
}

void Emitter::setBurst(int b) {
  burst = b;
}

void Emitter::on() {
	emitting = true;
	//timer = delay;
}

void Emitter::off() {
	emitting = false;
}

void Emitter::emit() {
  double rad = deg2rad(normDeg(uniform() * spread + rotation - spread/2));
  double px = cos(rad);
  double py = sin(rad);
  Particle *p = new Particle(lifespan);
	p->setPosition( px + x, py + y );
	p->setVelocity( velocity * px, velocity * py );
	particles.push_back(p);
}

void Emitter::update() {
	// Check for a new particle emission
	if (emitting) {
		timer--;
		if (!timer) {
      for (int j = 0; j < burst; j++)
			  emit();
			timer = delay;
		}
	}
	
	// Iterate over and update the individual particles
	for (list<Particle*>::iterator it = particles.begin(); it != particles.end(); it++) {
		Particle *p = (*it);
		p->update();
		if (p->isDead()) {
			particles.erase(it);
			it--;
			delete p;
		}
	}
}

void Emitter::render() {
	glPointSize(2.8);
	
  setLayer(LAYER_PARTICLES);
	glBegin(GL_POINTS);
	for (list<Particle*>::iterator it = particles.begin(); it != particles.end(); it++) {
		Particle *p = (*it);
		double life_ratio = (double)p->getLife() / (double)lifespan;		
		glColor3f( 0.25 + 0.75*life_ratio, life_ratio, 0.0 );
    vertex( p->getX(), p->getY() );
	}
	glEnd();
}


// This is awful, need a better way to do handle this
void Emitter::checkHits(Square *square) {
	for (list<Particle*>::iterator it = particles.begin(); it != particles.end(); it++) {
		Particle *p = (*it);
		if ( square->checkHit(p->getX(), p->getY()) ) {
      FX->add( new ParticleHit(p->getX(), p->getY()) );
			particles.erase(it);
			it--;
			delete p;
		}
	}
}


int Emitter::size() {
  return particles.size();
}


/**
 * Particle hit effect.
 */
ParticleHit::ParticleHit(double startX, double startY) {
  setDuration(40);
  x = startX;
  y = startY;
}

void ParticleHit::render() {
  glPointSize(3.0);
  
  if (getTimer() % 2) {
    glColor3f(1.0, 1.0, 0.0);
  }
  else {
    glColor3f(1.0, 0.0, 0.0);
  }
  
  setLayer(LAYER_EFFECTS);
  glBegin(GL_POINTS);
    vertex(x, y);
  glEnd();
}

