#ifndef BALLOON_ENTITY_H
#define BALLOON_ENTITY_H

#include <SDL.h>
#include "graphics.h"

class BalloonEntity {
public:
    void init(char glyphChar, int startX, SDL_Texture* normalTexture, SDL_Texture* popTexture);
    void update();
    void render(Graphics& gfx);
    void pop(); 
    bool isOutOfScreen() const;
    bool isPopped() const { return popped; }
    bool isAlive() const { return alive; }

    char glyph;
    int getX() const { return x; }
    int getY() const { return y; }
private:
    SDL_Texture* texture = nullptr;
    SDL_Texture* popSprite = nullptr;
    int x = 0, y = 0;
    int speed = -2;
    bool popped = false;
    bool alive = true;
    bool popping = false;
    int currentFrame = 0;
    Uint32 lastFrameTime = 0;
    static const int FRAME_SIZE = 80;
    static const int TOTAL_FRAMES = 6;
};

#endif
