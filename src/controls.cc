#include <stdlib.h>
#include <GLUT/GLUT.h>
#include "controls.h"

// Handles GLUT keydown events.
void keydown(unsigned char key, int x, int y) {
  switch (key) {
    case 'a': setAction(ACTION_LEFT); break;
    case 'd': setAction(ACTION_RIGHT); break;
    case 'w': setAction(ACTION_FORWARD); break;
    case 's': setAction(ACTION_BACK); break;
  }
}


// Handles GLUT keyup events.
void keyup(unsigned char key, int x, int y) {
  switch (key) {
    case 'a': unsetAction(ACTION_LEFT); break;
    case 'd': unsetAction(ACTION_RIGHT); break;
    case 'w': unsetAction(ACTION_FORWARD); break;
    case 's': unsetAction(ACTION_BACK); break;
    case '`': toggleAction(ACTION_SHOW_DEV_HUD); break;
    case 'q': exit(0); break;
  }
}


// Handles special keyboard events (function keys, arrows, etc.)
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


// Handles a mouse button press.
void mouse_button(int button, int state, int x, int y) {	
	if (button == GLUT_LEFT_BUTTON)
		(state == GLUT_DOWN) ? setAction(ACTION_SHOOT) : unsetAction(ACTION_SHOOT);
}


// Handles mouse movement when a button is being pressed (mouse drag).
void mouse_move(int x, int y) {
  return;
}


// Passive mouse movement handler
void mouse_passive(int x, int y) {
  return;
}

