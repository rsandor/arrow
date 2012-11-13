#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <math.h>
#include <string.h>
#include <list>
#include "emitter.h"
#include "player.h"
#include "square.h"
#include "util.h"
#include "effects.h"

using namespace std;

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



/**
 * FPS shit.
 */
double fps = 0.0;
int fps_frames;
int fps_current_time;
int fps_last_time;

void calcFPS() {
  fps_frames++;
  fps_current_time = glutGet(GLUT_ELAPSED_TIME);
  int elapsed = fps_current_time - fps_last_time;
  
  if (elapsed > 1000) {
    fps = (double)fps_frames / ((double)elapsed / 1000.0);
    fps_last_time = fps_current_time;
    fps_frames = 0;
  }
}





// Dev console switch
bool showDevHUD = true;

// The player entity
Player *player = new Player(); 

// And example square
list<Square*> squares;

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
	
	// Update the squares	
	for (list<Square*>::iterator square_it = squares.begin(); square_it != squares.end(); square_it++) {
		Square *square = (*square_it);
		
		if (square->isDead()) {
      FX->add( new SquareExplosion(square) );
			squares.erase(square_it);
			square_it--;
			delete square;
		}
		else {
			square->update(player->getX(), player->getY());
			emitter->checkHits(square);
		}
	}

	// Sync the emitter with the player
	emitter->setRotation( player->getRotation() );
	emitter->setPosition( player->getX(), player->getY() );
	emitter->update();
	
	// Manage global effects
  FX->update();
}

/**
 * Renders information about player position, etc. to the screen as an overlay.
 */
 
void renderString(const char *str, int x, int y) {
  glRasterPos2f(x, y);
  for (int i = 0; i < strlen(str); i++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
  }
}
 
void renderDevHUD() {
  if (!showDevHUD) return;
  
  char buffer[256];
  
  glPushMatrix();
  glLoadIdentity();
  glColor3f(0.3, 1.0, 0.3);
  
  glScalef(1.0, -1.0, 1.0);
  glTranslatef(0.0, -screen_height, 0.0);
  
  
  // Coordinates
  sprintf(buffer, "Position:  (%.2f, %.2f)", player->getX(), player->getY());
  renderString(buffer, 10, 20);
  
  // Active Particles from the Gun Emitter
  sprintf(buffer, "Particles: %d", emitter->size());
  renderString(buffer, 10, 40);
  
  // Number of effects
  sprintf(buffer, "Effects:   %d", FX->size());
  renderString(buffer, 10, 60);
  
  // Frames Per Second
  sprintf(buffer, "FPS        %.2f", fps);
  renderString(buffer, 10, 80);
  
  glPopMatrix();
}


/**
 * Renders the game graphics.
 */
void render() {
  // Render the scene
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  
  // Setup 2D rendering
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, screen_width, 0, screen_height, -1, 1);
  
  // Switch back to the modelview matrix
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity();
  
  
  // Center the camera on the player
  glTranslatef(
    -player->getX()+screen_width/2,
    -player->getY()+screen_height/2, 
    0.0
  );
  
  // Gridlines
  
  glPushMatrix();
  glLoadIdentity();
  
  int step = screen_width / 40;
  double ox = (int)player->getX() % step;
  double oy = (int)player->getY() % step;
  
  // Minor
  glColor3f(0.0, 0.05, 0.1);
  glLineWidth(1.0);
  
  glBegin(GL_LINES);
  for (int x = -(step + ox + step/2); x <= screen_width; x += step/2) {
    glVertex3f(x, 0, -0.5);
    glVertex3f(x, screen_height, -0.75);
  }
  
  for (int y = -(step + oy + step/2); y <= screen_height; y += step/2) {
    glVertex3f(0, y, -0.5);
    glVertex3f(screen_width, y, -0.75);
  }
  glEnd();
  
  // Major
  glColor3f(0.0, 0.1, 0.2);
  glLineWidth(1.0);
  
  glBegin(GL_LINES);
  for (int x = -(step + ox); x <= screen_width; x += step) {
    glVertex3f(x, 0, -0.5);
    glVertex3f(x, screen_height, -0.5);
  }
  
  for (int y = -(step + oy); y <= screen_height; y += step) {
    glVertex3f(0, y, -0.5);
    glVertex3f(screen_width, y, -0.5);
  }
  glEnd();
  
  
  
  glPopMatrix();
  
  
  // Render the player
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(screen_width/2, screen_height/2, 0.0);
	  
	  player->render();
	  
  glPopMatrix();
  
	// Render the squares
	for (list<Square*>::iterator square_it = squares.begin(); square_it != squares.end(); square_it++)
		(*square_it)->render();
	
	// Render the test emitter
	emitter->render();
  
  // Render effects
  FX->render();
  
  // Render the development HUD
  renderDevHUD();
  
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

    // Toggle the development HUD
    case '`': showDevHUD = !showDevHUD; break;

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
  glutPostRedisplay(); 
}


/**
 * GLUT display function, executes the main game loop and renders the scene.
 */
void display() {
  gameLoop();
  render();
  calcFPS();
  usleep(16666);
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
  glEnable(GL_DEPTH_TEST);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
  glEnable(GL_LINE_SMOOTH);
}


/**
 * Main method for the game. Initializes glut, gl, and starts the game loop.
 */
int main(int argc, char **argv) {
	initGLUT(argc, argv);
  initGL();

	srand( (unsigned) time( NULL ) );
	
	emitter->setSpread(20);
	emitter->setVelocity(5);
	emitter->setLifespan(2000);
	emitter->setDelay(1);
	
	
	// Create a bunch of random squares
	for (int i = 0; i < 5; i++) {
    double sx = screen_width * uniform();
    double sy = screen_height * uniform();
		Square *s = new Square();
		s->setPosition(sx, sy);
		squares.push_back(s);
	}

  glutMainLoop();
  return 0;
}

