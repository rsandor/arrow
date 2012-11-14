#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <GLUT/glut.h>
#include <list>

#include "emitter.h"
#include "player.h"
#include "square.h"
#include "util.h"
#include "effects.h"
#include "controls.h"

using namespace std;


int screen_width = 800;
int screen_height = 800;
double _currentLayer;
unsigned int keymap = 0;
Player *player = new Player(); 
list<Square*> squares;
Emitter *emitter = new Emitter();


void gameLoop() {
	// Update the player
	if ( checkAction(ACTION_LEFT) )
		player->rotateLeft();
  else if ( checkAction(ACTION_RIGHT) )
		player->rotateRight();
  
  if ( checkAction(ACTION_FORWARD) )
		player->moveForward();
  else if ( checkAction(ACTION_BACK) )
		player->moveBackward();
	else
		player->stop();
  
	player->update();

	
	// Update the enemies
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

  // Update the particles and effects
  if ( checkAction(ACTION_SHOOT) )
		emitter->on();
	else
		emitter->off();
		
	emitter->setRotation( player->getRotation() );
	emitter->setPosition( player->getX(), player->getY() );
	emitter->update();
	
	FX->update();
}

 
void renderString(const char *str, int x, int y) {
  glRasterPos2f(x, y);
  for (int i = 0; i < strlen(str); i++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
  }
}


void renderDevHUD() {
  if (!checkAction(ACTION_SHOW_DEV_HUD)) return;
  
  char buffer[256];
  
  glDisable(GL_DEPTH_TEST);
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
  sprintf(buffer, "FPS        %.2f", getFPS());
  renderString(buffer, 10, 80);
  
  glPopMatrix();
  glEnable(GL_DEPTH_TEST);
}


void renderGrid() {
  glPushMatrix();
  glLoadIdentity();
  
  int step = screen_width / 40;
  double ox = (int)player->getX() % step;
  double oy = (int)player->getY() % step;
  
  // Minor
  setLayer(LAYER_GRID_MINOR);
  glColor3f(0.0, 0.05, 0.1);
  glLineWidth(1.0);
  glBegin(GL_LINES);
  for (int x = -(step + ox + step/2); x <= screen_width; x += step/2) {
    vertex(x, 0);
    vertex(x, screen_height);
  }
  for (int y = -(step + oy + step/2); y <= screen_height; y += step/2) {
    vertex(0, y);
    vertex(screen_width, y);
  }
  glEnd();
  
  // Major
  setLayer(LAYER_GRID_MAJOR);
  glColor3f(0.0, 0.1, 0.2);
  glBegin(GL_LINES);
  for (int x = -(step + ox); x <= screen_width; x += step) {
    vertex(x, 0);
    vertex(x, screen_height);
  }
  for (int y = -(step + oy); y <= screen_height; y += step) {
    vertex(0, y);
    vertex(screen_width, y);
  }
  glEnd();
  
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
  glOrtho(0, screen_width, 0, screen_height, -100, 100);
  
  // Switch back to the modelview matrix
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity();
  
  // Center the camera on the player
  glTranslatef( -player->getX() + screen_width/2, -player->getY() + screen_height/2, 0.0 );
  
  // Render the game elements
  renderGrid();
  renderDevHUD();
  
  player->render();
	emitter->render();
  FX->render();
  
	for (list<Square*>::iterator square_it = squares.begin(); square_it != squares.end(); square_it++)
		(*square_it)->render();
	
  glFlush();
  glutSwapBuffers(); 
}


/**
 * Handles window resize events.
 * @param width New width of the window.
 * @param height New height of the window.
 */
void resize(int width, int height) {
  screen_width = width;
  screen_height = height;
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
 * Main method for the game. Initializes glut, gl, and starts the game loop.
 */
int main(int argc, char **argv) {
  srand( (unsigned) time( NULL ) );
  
  // Initialize GLUT
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
  
  // Initialize OpenGL
  glClearColor(0.0, 0.0, 0.07, 0.0);
  glShadeModel(GL_SMOOTH); 
  glViewport(0, 0, screen_width, screen_height);
  glEnable(GL_DEPTH_TEST);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
  glEnable(GL_LINE_SMOOTH);

  
	// Initialize the game state
	// TODO Pull this out into some form of game model
	emitter->setSpread(20);
	emitter->setVelocity(5);
	emitter->setLifespan(150);
	emitter->setDelay(1);
	
	for (int i = 0; i < 5; i++) {
    double sx = screen_width * uniform();
    double sy = screen_height * uniform();
		Square *s = new Square();
		s->setPosition(sx, sy);
		squares.push_back(s);
	}

  toggleAction(ACTION_SHOW_DEV_HUD);

  glutMainLoop();
  return 0;
}

