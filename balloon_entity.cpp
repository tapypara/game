#include "balloon_entity.h"

void BalloonEntity::init(char glyphChar, int startX, SDL_Texture* normalTex, SDL_Texture* popTex) {
    glyph = glyphChar;
    x = startX;
    y = SCREEN_HEIGHT;
    speed = -1 - rand() % 2;
    popped = false;
    alive = true;
    popping = false;
    texture = normalTex;
    popSprite = popTex;
}
void BalloonEntity::pop() {
    popped = true;
    popping = true;
    currentFrame = 0;
    lastFrameTime = SDL_GetTicks();
}
void BalloonEntity::update() {
    if (!popped) {
        y += speed;
    } else if (popping) {
        Uint32 now = SDL_GetTicks();
        if (now - lastFrameTime > 80) {
            currentFrame++;
            lastFrameTime = now;

            if (currentFrame >= TOTAL_FRAMES) {
                alive = false;
            }
        }
    }
}
void BalloonEntity::render(Graphics& gfx) {
    if (popping && popSprite) {
        SDL_Rect src = { 0, currentFrame * FRAME_SIZE, FRAME_SIZE, FRAME_SIZE }; 
        gfx.blitRect(popSprite, &src, x, y);
    } else if (!popped && texture) {
        gfx.renderTexture(texture, x, y);
    }
}
bool BalloonEntity::isOutOfScreen() const {
    return y + FRAME_SIZE < 0;
}
bool BalloonEntity::contains(int x, int y) const {
    int bx = getX();
    int by = getY();
    int bw = 80;  
    int bh = 80;
    SDL_Rect rect = {bx, by, bw, bh};
    SDL_Point point = {x, y};
    return SDL_PointInRect(&point, &rect);
}


