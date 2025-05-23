#include "graphics.h"
#include "balloon_entity.h"
#include "defs.h"
#include "menu.h"
#include "logic.h"
#include "button.h"
#include "pause.h"
#include "gameover.h"
#include "sound.h"
const char* WINDOW_TITLE = "POP BALLOONS TIME";
Graphics gfx;
GameState gameState = STATE_MENU;

std::map<char, SDL_Texture*> glyphTextures;
std::map<char, SDL_Texture*> popTextures;
std::vector<char> glyphPool = {'I', 'Z', 'V', 'O', 'F', 'P', '#'};
bool isDrawing = false;
std::vector<BalloonEntity> balloons;
Uint32 lastSpawn = 0;
const int minSpawnDelay = 500;
int spawnDelay = 2000;
int lives = 5;
int score = 0;
int highScore = 0;
bool gameOver = false;
bool running = true;
bool soundOn = true;
TTF_Font* font = nullptr;
SDL_Texture* skyTex = nullptr;
SDL_Texture* castleTex = nullptr;
SDL_Texture* dotTex = nullptr;
SDL_Texture* BgMenuTex = nullptr;
SDL_Texture* TutorialTex = nullptr;
SDL_Texture* heartTex = nullptr;
Mix_Music *menuMusic = nullptr;
Mix_Music *playingMusic = nullptr;
Mix_Chunk *scoring = nullptr;
Mix_Chunk *poping = nullptr;
Mix_Chunk *gameover = nullptr;
Button escapeingame = {  SCREEN_WIDTH - 250, 70 , 320 , 50 , "PAUSE"};
Button escapetutorial = {  SCREEN_WIDTH - 250, 70 , 320 , 50 , "TO MENU"};
TTF_Font* loadFont(const char* path, int size) {
    TTF_Font* font = TTF_OpenFont(path, size);
    if (!font) {
        SDL_Log("Font load error: %s", TTF_GetError());
    }
    return font;
}
void renderScores(int score, int highScore) {
    SDL_Color color = {255, 0, 255, 255};
    std::string text = "Score: " + std::to_string(score);
    std::string hiText = "High: " + std::to_string(highScore);
    gfx.renderText(text, SCREEN_WIDTH - 300, 10, color, font);
    gfx.renderText(hiText, SCREEN_WIDTH - 300, 40, color, font);
    renderButtonWithText(escapeingame);
}
void initGame() {
    gfx.init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    font = loadFont("assets/font.ttf", 24);
    heartTex = gfx.loadTexture("assets/heart.png");
    lastSpawn = SDL_GetTicks();
    glyphTextures['I'] = gfx.loadTexture("assets/balloon_i.png");
    glyphTextures['Z'] = gfx.loadTexture("assets/balloon_z.png");
    glyphTextures['V'] = gfx.loadTexture("assets/balloon_v.png");
    glyphTextures['O'] = gfx.loadTexture("assets/balloon_o.png");
    glyphTextures['F'] = gfx.loadTexture("assets/balloon_f.png");
    glyphTextures['P'] = gfx.loadTexture("assets/balloon_pi.png");
    glyphTextures['#'] = gfx.loadTexture("assets/balloon_vvv.png");
    popTextures['I'] = gfx.loadTexture("assets/balloon_i_pop.png");
    popTextures['Z'] = gfx.loadTexture("assets/balloon_z_pop.png");
    popTextures['V'] = gfx.loadTexture("assets/balloon_v_pop.png");
    popTextures['O'] = gfx.loadTexture("assets/balloon_o_pop.png");
    popTextures['F'] = gfx.loadTexture("assets/balloon_f_pop.png");
    popTextures['P'] = gfx.loadTexture("assets/balloon_pi_pop.png");
    popTextures['#'] = gfx.loadTexture("assets/balloon_vvv_pop.png");
    castleTex = gfx.loadTexture("assets/castle.png");
    dotTex = gfx.loadTexture("assets/dot.png");
    BgMenuTex = gfx.loadTexture("assets/bg.png");
    TutorialTex = gfx.loadTexture("assets/tutorial.png");
    skyTex = gfx.loadTexture("assets/sky.png");
    menuMusic = gfx.loadMusic("sfx/Menu.mp3");
    playingMusic = gfx.loadMusic("sfx/Playing.mp3");
    scoring = gfx.loadSound("sfx/Scoring.mp3");
    poping = gfx.loadSound("sfx/BalloonPoping.mp3");
    clicking = gfx.loadSound("sfx/Clicking.mp3");
    gameover = gfx.loadSound("sfx/GameOver.mp3");

}
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
void updateGame() {
    if(gameState == STATE_PLAYING)
    for (auto& b : balloons) {
        b.update();
        if (!b.isPopped() && b.isOutOfScreen()) {
            b.pop();
            lives--;
        }
    }
    if (lives <= 0) {
        gameOver = true;
        gfx.play(gameover);
        gameState = STATE_GAMEOVER;
        saveHighScore();
    }
    balloons.erase(std::remove_if(balloons.begin(), balloons.end(), [](const BalloonEntity& b) {
        return !b.isAlive();
    }), balloons.end());
}

void renderGame() {
    int wcas, hcas, wdot, hdot, wsky, hsky;
    SDL_QueryTexture(castleTex, nullptr, nullptr, &wcas, &hcas);
    SDL_QueryTexture(dotTex, nullptr, nullptr, &wdot, &hdot);
    SDL_QueryTexture(skyTex, nullptr, nullptr, &wsky, &hsky);
    SDL_RenderClear(gfx.renderer);
    gfx.renderTexture(skyTex, 0, SCREEN_HEIGHT - hsky);
    for (auto& b : balloons) {
        b.render(gfx);
    }


    gfx.renderTexture(castleTex, 0, SCREEN_HEIGHT - hcas + 5);
    for (int i = 0; i < lives; ++i) {
        gfx.renderTexture(heartTex, 10 + i * 40, 10);
    }
    renderScores(score, highScore);
    int k = drawingPoints.size();
    if(k > 1 ){
        for(int i = 0; i < k; i++) gfx.renderTexture(dotTex,drawingPoints[i].x - wdot/2 , drawingPoints[i].y - hdot/2);
    }
    gfx.presentScene();
}

int main(int argc, char* argv[]) {
    initGame();
    loadHighScore();
    gameState = STATE_MENU;
    SDL_Event e;
    loadHighScore();
    gfx.play(menuMusic);
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            switch (gameState) {
                case STATE_MENU:
                     balloons.clear();
                    score = 0;
                    lives = 5;
                    gameOver = false;
                    spawnDelay = 1500;
                    updateGameMenu(e, gameState);
                    break;
                case STATE_PLAYING:

                    if (clickOnButton(escapeingame,e)) {
                        gameState = STATE_PAUSED;
                    }
                    else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                        isDrawing = true;
                        currentStroke.clear();
                        drawingPoints.clear();
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        currentStroke.push_back({x, y});
                        drawingPoints.push_back({x, y});
                    }
                    else if (e.type == SDL_MOUSEMOTION && (e.motion.state & SDL_BUTTON_LMASK)) {
                        if (isDrawing) {
                                addPointFromMouse();
                        }
                    }
                    else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
                        isDrawing = false;
                        char matched = endStrokeAndCheckMatch(currentStroke);
                        if (matched != 'x') {
                            int combo = 0;
                            for (auto& b : balloons) {
                                if (!b.isPopped() && b.glyph == matched) {
                                    b.pop();
                                    gfx.play(poping);
                                    gfx.play(scoring);
                                    combo++;
                                }
                            }
                            if (combo > 0) {
                                int comboScore = combo * combo;
                                score += comboScore;
                                if (score > highScore) saveHighScore();
                                SDL_Log("Draw Match: %c  Combo: %d   +%d pts   Total: %d", matched, combo, comboScore, score);
                            }

                        }
                        drawingPoints.clear();
                        currentStroke.clear();
                    }
                    break;

                case STATE_PAUSED:
                    updatePause(e, gameState);
                    break;
                case STATE_HOWTOPLAY:
                    int w, h;
                    SDL_QueryTexture(TutorialTex, nullptr, nullptr, &w, &h);
                    gfx.renderTexture(TutorialTex, 0, SCREEN_HEIGHT - h + 5);
                    renderButtonWithText(escapetutorial);
                    gfx.presentScene();
                    if(clickOnButton(escapetutorial,e)) gameState = STATE_MENU;
                    break;
                case STATE_GAMEOVER:
                    balloons.clear();
                    score = 0;
                    lives = 3;
                    gameOver = false;
                    spawnDelay = 1500;
                    updateGameOver(e, gameState);
                    break;
            }
        }
        switch (gameState) {
            case STATE_MENU:
                renderMenu();
                break;
            case STATE_PLAYING:
                spawnBalloon();
                updateGame();
                renderGame();
                break;
            case STATE_PAUSED:
                renderPause();
                break;
            case STATE_GAMEOVER:
                renderGameOver();
                break;
            case STATE_HOWTOPLAY:
                gfx.clear();
                int w, h;
                 SDL_QueryTexture(TutorialTex, nullptr, nullptr, &w, &h);
                    gfx.renderTexture(TutorialTex, 0, SCREEN_HEIGHT - h + 5);
                    renderButtonWithText(escapetutorial);
                gfx.presentScene();
                break;
        }

        SDL_Delay(16);
    }

    gfx.quit();
    return 0;
}











