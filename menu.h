#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#include <SDL.h>

// Game state enum
enum GameState {
    STATE_MENU,
    STATE_PLAYING,
    STATE_GAMEOVER,
    STATE_PAUSED
};

// Khai báo các hàm menu
void loadHighScore();
void saveHighScore();
void renderMenu();
void handleMenuMouse(SDL_Event& e, GameState& state);

// Truy cập biến highScore từ bên ngoài nếu cần
extern int highScore;

#endif
