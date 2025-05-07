#ifndef GAME_BUTTON_H
#define GAME_BUTTON_H

#include <SDL.h>
#include <string>
struct Button{
    int x , y , w , h;
    std::string contents;
};
bool clickOnButton(Button bt,SDL_Event& e);
void renderButtonWithText(Button bt);
#endif
