/*
 * Implements the player entity.
 */

#include "player.h"
#include <GLUT/GLUT.h>

Player::Player() {
	size = 1.0;
	max_velocity = 0.005;
	max_rotation = 0.1;
}

void Player::render() {
  glPushMatrix();
  
  glTranslatef(x, y, 0.0);
  glRotatef(rotation, 0.0, 0.0, 1.0);
  
  glBegin(GL_LINE_LOOP);
  {
    glColor3f(0.25, 0.5, 1.0);
    glVertex3f(0.0, size, 0.0);
    glVertex3f(-(size/2), -(size/2), 0.0);
    glVertex3f(0.0, -(size/4), 0.0);
    glVertex3f((size/2), -(size/2), 0.0);
  }
  glEnd();
  
  glPopMatrix();
}

void Player::rotateLeft() {
	addRotation(max_rotation);
}

void Player::rotateRight() {
	addRotation(-max_rotation);
}

void Player::moveForward() {
	setVelocity(max_velocity);
}

void Player::moveBackward() {
	setVelocity(-max_velocity);
}

void Player::stop() {
	setVelocity(0.0);
}
