#ifndef GAME_BUTTON_H
#define GAME_BUTTON_H

#include <SDL.h>
#include <string>
#include "graphics.h"
struct Button{
    int x , y , w , h;
    std::string contents;
};
extern Graphics gfx;
extern TTF_Font* font;
extern Mix_Chunk *clicking;
bool clickOnButton(Button bt,SDL_Event& e);
void renderButtonWithText(Button bt);
#endif
