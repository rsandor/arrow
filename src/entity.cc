/*
 * Entity implementation.
 */

#include <GLUT/glut.h>
#include <math.h>
#include "util.h"
#include "entity.h"

Entity::Entity() {
	x = 0.0;
	y = 0.0;
	rotation = 0.0;
	velocity = 0.0;
}

void Entity::update() {
	double rad = deg2rad(rotation);
	x += velocity * cos(rad);
	y += velocity * sin(rad);
}

void Entity::render() {
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glEnd();
}

void Entity::setPosition(double newX, double newY) {
	x = newX;
	y = newY;
}

void Entity::setVelocity(double v) {
	velocity = v;
}

void Entity::setRotation(double r) {
	rotation = r;
	normalizeRotation();	
}

void Entity::addRotation(double dr) {
	rotation += dr;
	normalizeRotation();
}

void Entity::normalizeRotation() {
	if (rotation > 360.0)
		rotation -= 360.0;
	else if (rotation < 0)
		rotation += 360.0;
}

double Entity::getX() { return x; }
double Entity::getY() { return y; }
double Entity::getRotation() { return rotation; }
double Entity::getVelocity() { return velocity; }
