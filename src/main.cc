#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <math.h>
#include "emitter.h"
#include "player.h"
#include "square.h"
#include "util.h"

/**
 * Default screen size.
 */
int screen_width = 800;
int screen_height = 800;


/**
 * Player action map
 */
#define ACTION_LEFT      (1<<0)
#define ACTION_RIGHT     (1<<1)
#define ACTION_FORWARD   (1<<2)
#define ACTION_BACK      (1<<3)
#define ACTION_SHOOT     (1<<4)

unsigned int keymap = 0;

#define SET_KEY(key)    (keymap = keymap | (key))
#define UNSET_KEY(key)  (keymap = keymap & (~(key)))
#define CHECK_KEY(key)  (keymap & (key))


// The player entity
Player *player = new Player(); 

// And example square
Square *square = new Square();

// Sample "Gun" emitter (tied to player via game loop logic)
Emitter *emitter = new Emitter();


/**
 * Performs logic and math calculations prior to rendering a frame.
 */
void gameLoop() {
  
	// Handle player direction
  if ( CHECK_KEY(ACTION_LEFT) )
		player->rotateLeft();
  else if ( CHECK_KEY(ACTION_RIGHT) )
		player->rotateRight();
  
	// Handle Player Movement
  if ( CHECK_KEY(ACTION_FORWARD) )
		player->moveForward();
  else if ( CHECK_KEY(ACTION_BACK) )
		player->moveBackward();
	else
		player->stop();
  
	// Update the player
	player->update();

	// Update the emitter
	if ( CHECK_KEY(ACTION_SHOOT) )
		emitter->on();
	else
		emitter->off();
	
	// Sync the emitter with the player
	emitter->setRotation( player->getRotation() );
	emitter->setPosition( player->getX(), player->getY() );
	emitter->update();
	
	emitter->checkHits(square);
	
	// Update the square
	square->update(player->getX(), player->getY());
}


/**
 * Renders the game graphics.
 */
void render() {
  // Render the scene
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  glMatrixMode(GL_MODELVIEW); 
  
  glLoadIdentity();
  glTranslatef(0.0,0.0,-50); 
  
	// Render the player
	player->render();
  
	// Render the example square
	square->render();

	// Render the test emitter
	emitter->render();
  
  
  glFlush();
  glutSwapBuffers(); 
}


/**
 * Handles GLUT keydown events.
 * @param key Character code for the key being pressed.
 * @param x X-coordinate of the mouse.
 * @param y Y-coordinate of the mouse.
 */
void keydown(unsigned char key, int x, int y) {
  switch (key) {
    // Player Movement
    case 'a': SET_KEY(ACTION_LEFT); break;
    case 'd': SET_KEY(ACTION_RIGHT); break;
    case 'w': SET_KEY(ACTION_FORWARD); break;
    case 's': SET_KEY(ACTION_BACK); break;
  }
}


/**
 * Handles GLUT keyup events.
 */
void keyup(unsigned char key, int x, int y) {
  switch (key) {
    // Player Movement
    case 'a': UNSET_KEY(ACTION_LEFT); break;
    case 'd': UNSET_KEY(ACTION_RIGHT); break;
    case 'w': UNSET_KEY(ACTION_FORWARD); break;
    case 's': UNSET_KEY(ACTION_BACK); break;

    // Quit the game
    case 'q': exit(0); break;
  }
}


/**
 * Handles special keyboard events (function keys, arrows, etc.)
 * @param key Code for the key being pressed.
 * @param x X-coordinate of the mouse.
 * @param y Y-coordinate of the mouse.
 */
void keyboard_s(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      break;
    case GLUT_KEY_DOWN:
      break;
    case GLUT_KEY_LEFT:
      break;
    case GLUT_KEY_RIGHT:
      break;
  }
}


/**
 * Handles a mouse button press.
 * @param button Which button is being pressed.
 * @param state Which state (up, down) the button is in.
 * @param x X-coordinate of the mouse.
 * @param y Y-coordinate of the mosue.
 */
void mouse_button(int button, int state, int x, int y) {
	
	if (button == GLUT_LEFT_BUTTON) {
		(state == GLUT_DOWN) ? SET_KEY(ACTION_SHOOT) : UNSET_KEY(ACTION_SHOOT);
	}
	
  return;
}


/**
 * Handles mouse movement when a button is being pressed (mouse drag).
 * @param x X-coordinate of the mouse.
 * @param y Y-coordinate of the mouse.
 */
void mouse_move(int x, int y) {
  return;
}


/**
 * Handles window resize events.
 * @param width New width of the window.
 * @param height New height of the window.
 */
void resize(int width, int height) {
  screen_width = width;
  screen_height=height;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,screen_width,screen_height); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity(); 
  gluPerspective(
    45.0f,
    (GLfloat)screen_width / (GLfloat)screen_height,
    1.0f,
    1000.0f
  );
  glutPostRedisplay (); 
}


/**
 * GLUT display function, executes the main game loop and renders the scene.
 */
void display() {
  gameLoop();
  render();
}


/**
 * Initializes GLUT
 */
void initGLUT(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(screen_width, screen_height);
  glutInitWindowPosition(0,0);
  glutCreateWindow("arrow");
  glutFullScreen();
  
  glutIgnoreKeyRepeat(1);
  glutKeyboardFunc(keydown);
  glutKeyboardUpFunc(keyup);
  glutSpecialFunc(keyboard_s);
  
  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutReshapeFunc(resize);
  
  
  glutMotionFunc(mouse_move);
  glutMouseFunc(mouse_button);
  glutSetCursor(GLUT_CURSOR_NONE);
}


/**
 * Initializes OpenGL for drawing.
 */
void initGL() {
  glClearColor(0.0, 0.0, 0.07, 0.0);
  glShadeModel(GL_SMOOTH); 
  glViewport(0, 0, screen_width, screen_height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(
    45.0f,
    (GLfloat) screen_width / (GLfloat)screen_height,
    1.0f,
    1000.0f
  );
  glEnable(GL_DEPTH_TEST);
  glPolygonMode (GL_FRONT_AND_BACK, GL_LINE); 
}


/**
 * Main method for the game. Initializes glut, gl, and starts the game loop.
 */
int main(int argc, char **argv) {
	initGLUT(argc, argv);
  initGL();

	srand( (unsigned) time( NULL ) );
	
	emitter->setPosition(0, 0);
	emitter->setRotation(45);
	emitter->setSpread(45);
	emitter->setVelocity(0.01);
	emitter->setLifespan(2000);
	emitter->setDelay(100);
	
	square->setPosition(10, 10);
	
	/*
	emitter->setPosition(0, 0);
	emitter->setRotation(45);
	emitter->setSpread(20);
	emitter->setVelocity(0.01);
	emitter->setLifespan(2000);
	emitter->setDelay(10);
	*/

  glutMainLoop();
  return 0;
}

