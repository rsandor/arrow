/*
 * Manages effects like explosions, shields, and laser hits for the game.
 */

#include <list>
#pragma once

/**
 * Abstract base class for all graphics effects for
 * use with the effects manager.
 */
class Effect {
  public:
    Effect();
    Effect(int);
    void setDuration(int);
    int getDuration();
    int getTimer();
    void update();
    bool isDead();
    virtual void render() = 0;
    
  private:
    int duration;
    int timer;
};

/**
 * Manages, renders, and updates all game effects.
 */
class EffectsManager {
  public:
    void add(Effect *);
    void render();
    void update();
    int size();
  private:
    std::list<Effect*> effects;
};

extern EffectsManager *FX;
