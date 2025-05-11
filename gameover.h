#ifndef GAME_OVER_H
#define GAME_OVER_H
#include "defs.h"
extern Graphics gfx;
extern int score;
extern Mix_Music *menuMusic;
extern Mix_Music *playingMusic;
extern bool soundOn;
void renderGameOver();
void updateGameOver(SDL_Event& e,GameState& gameState);
#endif

