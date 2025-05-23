#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "graphics.h"
#include "defs.h"
#include "menu.h"
#include "button.h"
using namespace std;
Mix_Chunk *clicking = nullptr;
bool clickOnButton(Button bt, SDL_Event& e){
    int x , y;
    if(e.type == SDL_MOUSEBUTTONDOWN){
    SDL_GetMouseState(&x, &y);
    if( x > bt.x && x < bt.x + bt.w && y > bt.y && y < bt.y + bt.h){
        gfx.play(clicking);
    SDL_Delay(500);
        return true;}
    }
    return false;
}
void renderButtonWithText(Button bt){
     SDL_Color color = {0, 255, 255, 255};
    gfx.renderText(bt.contents, bt.x + 30, bt.y + 10, color, font);
}
