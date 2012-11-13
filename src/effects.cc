#include <iostream>
#include "effects.h"
#include "GLUT/GLUT.h"

using namespace std;

/*
 * Effect base class implementation.
 */

Effect::Effect() {
  duration = timer = 0;
}

Effect::Effect(int d) {
  duration = timer = d;
}

void Effect::update() {
  timer = !timer ? 0 : timer - 1;
}

bool Effect::isDead() {
  return timer == 0;
}

void Effect::setDuration(int d) {
  duration = timer = d;
}

int Effect::getDuration() { return duration; }
int Effect::getTimer() { return timer; }


/*
 * Effects Manager implementation.
 */
void EffectsManager::add(Effect *effect) {
  effects.push_back(effect);
}

void EffectsManager::render() {
  glPushMatrix();
  glTranslatef(0.0, 0.0, 0.5);
  
  for (list<Effect *>::iterator it = effects.begin(); it != effects.end(); it++) {
    (*it)->render();
  }
  
  glPopMatrix();
}

void EffectsManager::update() {
  for (list<Effect *>::iterator it = effects.begin(); it != effects.end(); it++) {
    Effect *effect = (*it);
    effect->update();
    if (effect->isDead()) {
      effects.erase(it);
      it--;
      delete effect;
    }
  }
}

int EffectsManager::size() {
  return effects.size();
}

EffectsManager *FX = new EffectsManager();
