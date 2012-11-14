/*
 * Implements the player entity.
 */

#include <GLUT/GLUT.h>
#include "player.h"
#include "util.h"


Player::Player() {
	size = 20.0;
	max_velocity = 2.5;
	max_rotation = 4.0;
}

void Player::render() {
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(screen_width/2, screen_height/2, 0.0);
  glRotatef(rotation, 0.0, 0.0, 1.0);
  
  setLayer(LAYER_PLAYER_FG);
  glColor3f(0.25, 0.5, 1.0);
  glBegin(GL_POLYGON);
    vertex(0.0, size);
    vertex(-(size/2), -(size/2));
    vertex(0.0, -(size/4));
    vertex((size/2), -(size/2));
    vertex(0.0, size);
  glEnd();
  
  setLayer(LAYER_PLAYER_BG);
  glLineWidth(5.0);
  glColor3f(0.1, 0.2, 0.4);
  glBegin(GL_LINE_LOOP);
    vertex(0.0, size);
    vertex(-(size/2), -(size/2));
    vertex(0.0, -(size/4));
    vertex((size/2), -(size/2));
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
