#include "defs.h"
#include "button.h"
#include "pause.h"
using namespace std;
Button resumeBt  = { 480, 360, 320, 50, "Resum Game"};
Button escapeBt   = { 480, 430, 320, 50, "To Menu"};
void renderPause() {
    renderButtonWithText(resumeBt);
    renderButtonWithText(escapeBt);
    gfx.presentScene();
}
void updatePause(SDL_Event& e,GameState& gameState){
    if(clickOnButton(resumeBt,e)) {
        gameState = STATE_PLAYING;
    }
    if(clickOnButton(escapeBt,e)){ gameState = STATE_MENU;
    if(soundOn){
            Mix_HaltMusic();
            gfx.play(menuMusic);
        }
    }
}
