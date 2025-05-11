#ifndef _DEFS__H
#define _DEFS__H
#include <SDL.h>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
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


