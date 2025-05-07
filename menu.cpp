#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <fstream>
#include "graphics.h"
#include "defs.h"
#include "menu.h"
#include "button.h"
using namespace std;
extern Graphics gfx;
extern bool soundOn;
extern bool running;
extern int score;
extern SDL_Texture* BgMenuTex;
extern int highScore;
Button playBt   = { 480, 220, 320, 50 ,"Play Game"};
Button toggleBt  = { 480, 290, 320, 50, "Sound : ON"};
Button quitBt   = { 480, 430, 320, 50, "Quit Game"};
Button tutorialBt   = { 480, 360, 320, 50, "Tutorial"};
Button showHiScore = { SCREEN_WIDTH - 250, 40, 320, 50, "tmp"};
void loadHighScore(){
    std::ifstream in("highscore.txt");
    if (in.is_open()){
        in >> highScore;
        in.close();
    }
}
void saveHighScore(){
    if (score > highScore){
        highScore = score;
        std::ofstream out("highscore.txt");
        if (out.is_open()){
            out << highScore;
            out.close();
        }
    }
}
void renderMenu(){
    gfx.clear();
    SDL_Color color = {255, 255, 255, 255};
    int w, h;
    SDL_QueryTexture(BgMenuTex, nullptr, nullptr, &w, &h);
    gfx.renderTexture(BgMenuTex, 0, SCREEN_HEIGHT - h);
    renderButtonWithText(playBt);
    renderButtonWithText(toggleBt);
    renderButtonWithText(tutorialBt);
    renderButtonWithText(quitBt);
    string hiText = "High: " + to_string(highScore);
    showHiScore.contents = hiText;
    renderButtonWithText(showHiScore);
    gfx.presentScene();
}
void updateGameMenu(SDL_Event& e,GameState& gameState){
    loadHighScore();
    if(clickOnButton(playBt,e)) gameState = STATE_PLAYING;
    if(clickOnButton(toggleBt,e)){
        if(soundOn){ toggleBt.contents ="Sound : OFF";
        soundOn = !soundOn;
        }
        else{ toggleBt.contents ="Sound : ON";
        soundOn = !soundOn;
        }
    }
    if(clickOnButton(tutorialBt,e)) gameState = STATE_HOWTOPLAY;
    if(clickOnButton(quitBt,e)) running = false;
}
