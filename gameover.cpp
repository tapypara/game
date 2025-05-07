#include <SDL.h>
#include <string>
#include "graphics.h"
#include "defs.h"
#include "button.h"
#include "gameover.h"
using namespace std;
extern Graphics gfx;
extern int score;
Button playAgainBt  = { 480, 360, 320, 50, "Try Again"};
Button quit1Bt   = { 480, 430, 320, 50, "To Menu"};
void renderGameOver(){
    renderButtonWithText(playAgainBt);
    renderButtonWithText(quit1Bt);
    gfx.presentScene();
}
void updateGameOver(SDL_Event& e,GameState& gameState){
    if(clickOnButton(playAgainBt,e)){ gameState = STATE_PLAYING;}
    if(clickOnButton(quit1Bt,e)) gameState = STATE_MENU;
}

