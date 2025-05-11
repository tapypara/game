#ifndef PAUSE_H
#define PAUSE_H
#include "defs.h"
extern Graphics gfx;
extern bool soundOn;
extern Mix_Music *menuMusic;
extern Mix_Music *playingMusic;
void renderPause();
void updatePause(SDL_Event& e,GameState& gameState);
#endif

