#include <iostream>
#include <math.h>
#include "GLUT/GLUT.h"
#include "square.h"

using namespace std;

Square::Square() {
	wiggle = 0.0;
	d_wiggle = 0.04;
	max_wiggle = 15.0;
	velocity = 0.0005;
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
		addRotation( (diff < 0) ? -0.02 : 0.02 );
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
	
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(0.5, -0.5, 0.0);
		glVertex3f(0.5, 0.5, 0.0);
		glVertex3f(-0.5, 0.5, 0.0);
	glEnd();
	
	glPopMatrix();
}