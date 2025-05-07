#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#include <SDL.h>

void loadHighScore();
void saveHighScore();
void updateGameMenu(SDL_Event& e, GameState& gameState);
void renderMenu();


#endif
