/*
 * Implements the player entity.
 */

#include <GLUT/GLUT.h>
#include "player.h"
#include "util.h"


Player::Player() {
	scale = 20.0;
	max_velocity = 2.5;
	max_rotation = 4.0;
}

void Player::render() {
  glPushMatrix();
  glRotatef(rotation, 0.0, 0.0, 1.0);
  glScalef(scale, scale, 1.0);
  
  setLayer(LAYER_PLAYER_FG);
  glColor3f(0.25, 0.5, 1.0);
  glBegin(GL_POLYGON);
    vertex(0.0, 1);
    vertex(-0.5, -0.5);
    vertex(0.0, -0.25);
    vertex(0.5, -0.5);
    vertex(0.0, 1);
  glEnd();
  
  setLayer(LAYER_PLAYER_BG);
  glColor3f(0.1, 0.2, 0.4);
  glScalef(1.3, 1.3, 1.0);
  
  glBegin(GL_POLYGON);
    vertex(0.0, 1);
    vertex(-0.5, -0.5);
    vertex(0.0, -0.25);
    vertex(0.5, -0.5);
    vertex(0.0, 1);
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
