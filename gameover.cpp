#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <fstream>
#include "graphics.h"
#include "defs.h"
#include "menu.h"
#include "button.h"
#include "vector"
#include "balloon_entity.h"
#include "gameover.h"
using namespace std;
extern Graphics gfx;
extern TTF_Font* font;
extern bool running;
extern bool soundOn;
extern int score;
extern std::vector<BalloonEntity> balloons;
Button playAgainBt  = { 480, 360, 320, 50, "Play Game"};
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

