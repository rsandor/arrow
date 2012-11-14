#include <GLUT/GLUT.h>
#include "util.h"

double fps = 0.0;
int fps_frames;
int fps_current_time;
int fps_last_time;

// Called after rendering to calculate frames per second
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

// Returns the current FPS value
double getFPS() {
  return fps;
}
