#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <fstream>
#include "graphics.h"
#include "defs.h"
#include "menu.h"

// Các biến toàn cục được khai báo từ main.cpp
extern Graphics gfx;
extern TTF_Font* font;
extern bool running;
extern bool soundOn;
extern int score;

// Kích thước và vị trí các nút trong menu
SDL_Rect playBtn    = { 480, 220, 320, 50 };
SDL_Rect saveBtn    = { 480, 290, 320, 50 };
SDL_Rect toggleBtn  = { 480, 360, 320, 50 };
SDL_Rect quitBtn    = { 480, 430, 320, 50 };

// Đọc high score từ file
void loadHighScore() {
    std::ifstream in("highscore.txt");
    if (in.is_open()) {
        in >> highScore;
        in.close();
    }
}

// Ghi high score vào file
void saveHighScore() {
    if (score > highScore) {
        highScore = score;
        std::ofstream out("highscore.txt");
        if (out.is_open()) {
            out << highScore;
            out.close();
        }
    }
}

// Vẽ một nút đơn bằng text
void renderButton(const std::string& label, SDL_Rect rect) {
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Blended(font, label.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gfx.renderer, surface);
    SDL_Rect dst = { rect.x + 20, rect.y, surface->w, surface->h };
    SDL_RenderCopy(gfx.renderer, texture, nullptr, &dst);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

// Vẽ toàn bộ menu
void renderMenu() {
    gfx.clear();

    renderButton("Play Game", playBtn);
    renderButton("Save High Score", saveBtn);
    renderButton(soundOn ? "Sound: ON" : "Sound: OFF", toggleBtn);
    renderButton("Quit Game", quitBtn);

    // Vẽ dòng high score màu xanh nhạt
    SDL_Color hiColor = {180, 200, 255, 255};
    std::string hiText = "High Score: " + std::to_string(highScore);
    SDL_Surface* s = TTF_RenderText_Blended(font, hiText.c_str(), hiColor);
    SDL_Texture* t = SDL_CreateTextureFromSurface(gfx.renderer, s);
    SDL_Rect pos = {SCREEN_WIDTH - s->w - 20, 20 + s->h * 2, s->w, s->h};
    SDL_RenderCopy(gfx.renderer, t, nullptr, &pos);
    SDL_FreeSurface(s);
    SDL_DestroyTexture(t);

    gfx.presentScene();
}

// Xử lý sự kiện chuột trong menu
void handleMenuMouse(SDL_Event& e, GameState& state) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mx = e.button.x;
        int my = e.button.y;
        SDL_Point p = {mx, my};

        if (SDL_PointInRect(&p, &playBtn)) {
            state = STATE_PLAYING;
            score = 0;
        }
        else if (SDL_PointInRect(&p, &saveBtn)) {
            saveHighScore();
        }
        else if (SDL_PointInRect(&p, &toggleBtn)) {
            soundOn = !soundOn;
        }
        else if (SDL_PointInRect(&p, &quitBtn)) {
            running = false;
        }
    }
}
