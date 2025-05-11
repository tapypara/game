#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H
#include "graphics.h"
#include "defs.h"
#include "button.h"
extern Graphics gfx;
extern bool soundOn;
extern bool running;
extern int score;
extern SDL_Texture* BgMenuTex;
extern int highScore;
extern Mix_Music *menuMusic;
extern Mix_Music *playingMusic;
extern Button playBt;
extern Button toggleBt;
extern Button quitBt;
extern Button tutorialBt;
extern Button showHiScore;
void loadHighScore();
void saveHighScore();
void updateGameMenu(SDL_Event& e, GameState& gameState);
void renderMenu();
#endif
