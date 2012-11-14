#pragma once

#define ACTION_LEFT           (1<<0)
#define ACTION_RIGHT          (1<<1)
#define ACTION_FORWARD        (1<<2)
#define ACTION_BACK           (1<<3)
#define ACTION_SHOOT          (1<<4)
#define ACTION_SHOW_DEV_HUD   (1<<5)

#define setAction(key)    (keymap = keymap | (key))
#define unsetAction(key)  (keymap = keymap & (~(key)))
#define checkAction(key)  (keymap & (key))
#define toggleAction(key) (checkAction(key) ? unsetAction(key) : setAction(key))

void keydown(unsigned char, int, int);
void keyup(unsigned char, int, int);
void keyboard_s(int, int, int);
void mouse_button(int, int, int, int);
void mouse_move(int, int);
void mouse_passive(int, int);

extern unsigned int keymap;
