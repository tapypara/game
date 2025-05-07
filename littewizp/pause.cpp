#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <fstream>
#include "graphics.h"
#include "defs.h"
#include "menu.h"
#include "button.h"
#include "pause.h"
extern Graphics gfx;
extern TTF_Font* font;
extern bool running;
extern bool soundOn;
extern int score;
extern int highScore;
Button resumeBt  = { 480, 360, 320, 50, "Resum Game"};
Button escapeBt   = { 480, 430, 320, 50, "To Menu"};
void renderPause() {
    renderButtonWithText(resumeBt);
    renderButtonWithText(escapeBt);
    gfx.presentScene();
}
void updatePause(SDL_Event& e,GameState& gameState){
    if(clickOnButton(resumeBt,e)) gameState = STATE_PLAYING;
    if(clickOnButton(escapeBt,e)) gameState = STATE_MENU;
}
