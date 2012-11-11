#include "effects.h"

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


/*
 * Effects Manager implementation.
 */
 
EffectsManager::EffectsManager() {
}
 
void EffectsManager::add(Effect *effect) {
  effects.push_back(effect);
}

void EffectsManager::render() {
  for (list<Effect *>::iterator it = effects.begin(); it != effects.end(); it++) {
    (*it)->render();
  }
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

EffectsManager *man = new EffectsManager();

EffectsManager *getEffectsManager() {
  return man;
}

void addEffect(Effect *effect) {
  man->add(effect);
}
