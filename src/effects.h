/*
 * Manages effects like explosions, shields, and laser hits for the game.
 */

#include <list>
#pragma once

class Effect {
  public:
    Effect();
    Effect(int);
    void setDuration(int);
    void update();
    bool isDead();
    virtual void render() = 0;
    
  protected:
    int duration;
    int timer;
};

class EffectsManager {
  public:
    EffectsManager();
    void add(Effect *);
    void render();
    void update();
  private:
    std::list<Effect*> effects;
};

void addEffect(Effect*);
EffectsManager *getEffectsManager();
