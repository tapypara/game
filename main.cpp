#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <string>
#include <fstream>
#include "graphics.h"
#include "balloon_entity.h"
#include "defs.h"
#include "cloud.h"
#include "menu.h"
const char* WINDOW_TITLE = "littlewizp";

Graphics gfx;
TTF_Font* font = nullptr;
SDL_Texture* heartTex = nullptr;
CloudManager cloud;
GameState gameState = STATE_MENU;
std::map<char, SDL_Texture*> glyphTextures;
std::map<char, SDL_Texture*> popTextures;
std::vector<char> glyphPool = {'I', 'Z', 'V', 'O', 'F', 'P', '#'};

std::vector<BalloonEntity> balloons;
Uint32 lastSpawn = 0;
int spawnDelay = 1500;
const int minSpawnDelay = 500;
int lives = 3;
int score = 0;
bool gameOver = false;
bool running = true;
bool soundOn = true;
SDL_Texture* castleTex = nullptr;
int highScore = 0;
// Load font
TTF_Font* loadFont(const char* path, int size) {
    TTF_Font* font = TTF_OpenFont(path, size);
    if (!font) {
        SDL_Log("Font load error: %s", TTF_GetError());
    }
    return font;
}

// Vẽ điểm
void renderScores(int score, int highScore) {
    SDL_Color color = {255, 255, 255, 255};
    std::string text = "Score: " + std::to_string(score);
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gfx.renderer, surface);

    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    SDL_Rect dst = {SCREEN_WIDTH - w - 20, 10, w, h};
    SDL_RenderCopy(gfx.renderer, texture, nullptr, &dst);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    // High score
    std::string hiText = "High: " + std::to_string(highScore);
    surface = TTF_RenderText_Blended(font, hiText.c_str(), color);
    texture = SDL_CreateTextureFromSurface(gfx.renderer, surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    SDL_Rect hiDst = {SCREEN_WIDTH - w - 20, 10 + h + 5, w, h};
    SDL_RenderCopy(gfx.renderer, texture, nullptr, &hiDst);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

// Khởi tạo game
void initGame() {
    gfx.init();
    font = loadFont("assets/font.ttf", 24);
    heartTex = gfx.loadTexture("assets/heart.png");
    cloud.init(gfx);
    lastSpawn = SDL_GetTicks();
    loadHighScore();
    glyphTextures['I'] = gfx.loadTexture("assets/balloon_i.png");
    glyphTextures['Z'] = gfx.loadTexture("assets/balloon_z.png");
    glyphTextures['V'] = gfx.loadTexture("assets/balloon_v.png");
    glyphTextures['O'] = gfx.loadTexture("assets/balloon_o.png");
    glyphTextures['F'] = gfx.loadTexture("assets/balloon_f.png");
    glyphTextures['P'] = gfx.loadTexture("assets/balloon_pi.png");
    glyphTextures['#'] = gfx.loadTexture("assets/balloon_vvv.png");
    castleTex = gfx.loadTexture("assets/castle.png");
    popTextures['I'] = gfx.loadTexture("assets/balloon_i_pop.png");
    popTextures['Z'] = gfx.loadTexture("assets/balloon_z_pop.png");
    popTextures['V'] = gfx.loadTexture("assets/balloon_v_pop.png");
    popTextures['O'] = gfx.loadTexture("assets/balloon_o_pop.png");
    popTextures['F'] = gfx.loadTexture("assets/balloon_f_pop.png");
    popTextures['P'] = gfx.loadTexture("assets/balloon_pi_pop.png");
    popTextures['#'] = gfx.loadTexture("assets/balloon_vvv_pop.png");
}

// Xử lý phím bấm
void handleInput(SDL_Event& e) {
    if (e.type == SDL_QUIT) running = false;

    if (!gameOver && e.type == SDL_KEYDOWN) {
        char key = static_cast<char>(e.key.keysym.sym);
        key = toupper(key);
        if (key == '3') key = '#';

        int combo = 0;
        for (auto& b : balloons) {
            if (!b.isPopped() && b.glyph == key) {
                b.pop();
                combo++;
            }
        }

        if (combo > 0) {
    int comboScore = combo * combo;
    score += comboScore;

    if (score > highScore) {
        highScore = score;
    }

    SDL_Log("Combo: %d  +%d pts  Total: %d", combo, comboScore, score);
}

    }
}

// Tạo bóng mới
void spawnBalloon() {
    Uint32 now = SDL_GetTicks();
    if (!gameOver && now - lastSpawn >= spawnDelay) {
        char glyph = glyphPool[rand() % glyphPool.size()];
        int randX = 150 + rand() % (SCREEN_WIDTH - 379);
        BalloonEntity b;
        b.init(glyph, randX, glyphTextures[glyph], popTextures[glyph]);
        balloons.push_back(b);

        lastSpawn = now;
        if (spawnDelay > minSpawnDelay) spawnDelay -= 20;
    }
}

// Cập nhật bóng, va chạm mây đen, trừ mạng
void updateGame() {
    for (auto& b : balloons) {
        b.update();

        if (!b.isPopped() && cloud.isUnderDarkCloud(b.getX(), b.getY(), 80, 80)) {
            b.pop();
            lives--;
        }

        if (!b.isPopped() && b.isOutOfScreen()) {
            b.pop();
            lives--;
        }
    }
    if (lives <= 0) {
        gameOver = true;
        gameState = STATE_GAMEOVER;
        saveHighScore();
    }
    balloons.erase(
        std::remove_if(balloons.begin(), balloons.end(),
            [](const BalloonEntity& b) { return !b.isAlive(); }),
        balloons.end()
    );

    cloud.update();
}

// Vẽ toàn bộ màn hình
void renderGame() {
  SDL_RenderClear;

    cloud.render(gfx);

    for (auto& b : balloons) {
        b.render(gfx);
    }

    int w, h;
    SDL_QueryTexture(castleTex, nullptr, nullptr, &w, &h);
    gfx.renderTexture(castleTex, 0, SCREEN_HEIGHT - h);

    for (int i = 0; i < lives; ++i) {
        gfx.renderTexture(heartTex, 10 + i * 40, 10);
    }

    renderScores(score,highScore);
    gfx.presentScene();
}

// Hàm chính
int main(int argc, char* argv[]) {
    srand(SDL_GetTicks());
    initGame();
    loadHighScore();
    gameState = STATE_MENU;

    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;

            if (gameState == STATE_MENU) {
                handleMenuMouse(e, gameState);
            }
           else if (gameState == STATE_PLAYING) {
                if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_ESCAPE)
                    gameState = STATE_PAUSED;
           else handleInput(e);  // 👈 xử lý combo, phá bóng
    }
}

            else if (gameState == STATE_PAUSED && e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) gameState = STATE_PLAYING;
                if (e.key.keysym.sym == SDLK_q) gameState = STATE_MENU;
            }
            else if (gameState == STATE_GAMEOVER && e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RETURN) {
                    gameState = STATE_PLAYING;
                    balloons.clear(); score = 0; lives = 3; gameOver = false;
                    spawnDelay = 1500;
                }
                if (e.key.keysym.sym == SDLK_ESCAPE) gameState = STATE_MENU;
            }
        }

        if (gameState == STATE_MENU) renderMenu();
        else if (gameState == STATE_PLAYING) {
            spawnBalloon();
            updateGame();
            renderGame();
        }
        else if (gameState == STATE_PAUSED || gameState == STATE_GAMEOVER) {
            renderGame();  // giữ nguyên khung
        }

        SDL_Delay(16);
    }
    gfx.quit();
    return 0;
}
