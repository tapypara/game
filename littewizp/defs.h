#ifndef _DEFS__H
#define _DEFS__H

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;
extern const char* WINDOW_TITLE;
enum GameState {
    STATE_MENU,
    STATE_PLAYING,
    STATE_HOWTOPLAY,
    STATE_GAMEOVER,
    STATE_PAUSED
};

#endif


