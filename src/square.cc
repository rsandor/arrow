#include <iostream>
#include <math.h>
#include "GLUT/GLUT.h"
#include "square.h"
#include "effects.h"

using namespace std;

/*
 * Square implementation
 */

Square::Square() {
	wiggle = 0.0;
	d_wiggle = 0.04;
	max_wiggle = 15.0;
	velocity = 0.05;
	health = 1000;
  scale = 20.0;
}

bool Square::checkHit(double bx, double by) {
  if (bx >= x - (scale/2) && bx <= x + (scale/2) && by >= y - (scale/2) && by <= y + (scale/2)) {
		health -= 5;
		if (health <= 0) {
			health = 0;
		}
		return true;
	}
	return false;
}

bool Square::isDead() {
	return health <= 0;
}

void Square::update(double px, double py) {	
	// Track the player
	double dx = x - px;
	double dy = y - py;
	double m = sqrt(dx*dx + dy*dy);
	dx /= m; 
	dy /= m;
	double target_rotation = 90.0 + atan2(dy, dx) * 180.0 / M_PI;
	double diff = target_rotation - rotation;
	
	if (fabs(diff) > 0.1) {
		addRotation( (diff < 0) ? -1 : 1 );
	}
	
	// Add the funny little wiggle walk
	wiggle += d_wiggle;
	if (wiggle >= max_wiggle) {
		wiggle = max_wiggle;
		d_wiggle *= -1;
	}
	else if (wiggle <= -max_wiggle) {
		wiggle = -max_wiggle;
		d_wiggle *= -1;
	}

	Entity::update();
}

void Square::render() {
	glPushMatrix();
	
	
	glTranslatef(x, y, 0.0);
  glRotatef(rotation, 0.0, 0.0, 1.0);
	glRotatef(wiggle, 0.0, 0.0, 1.0);
	glScalef(scale, scale, 1.0);

	double red = (double)health / 100.0;
	if (red < 0.0) red = 0.0;
	
	glColor3f(0.5 + 0.5*red, 0.5*red, 0.0);
	glBegin(GL_POLYGON);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(0.5, -0.5, 0.0);
		glVertex3f(0.5, 0.5, 0.0);
		glVertex3f(-0.5, 0.5, 0.0);
		glVertex3f(-0.5, -0.5, 0.0);
	glEnd();
	
	glPopMatrix();
}


/*
 * Explosion effect implementation.
 */
SquareExplosion::SquareExplosion(Square *square) {
  setDuration(600);
  x = square->getX();
  y = square->getY();
}

void SquareExplosion::render() {
  int duration = getDuration();
  int timer = getTimer();
  
  double distance = 2.0*(duration-timer)/duration;
  double color = timer / duration;
  
  glPushMatrix();
  glTranslatef(x, y, 0.0);
  
  glPointSize(3.0);
  glColor3f(0.75+0.25*color, 1.0-color, 0.0);
  
  glBegin(GL_POINTS);
    for (int i = 0; i < 10; i++) {
      double px = cos(i*M_PI/5) * distance;
      double py = sin(i*M_PI/5) * distance;
      glVertex3f(px, py, 0.0);
    }
  glEnd();
  
  glPopMatrix();
}



