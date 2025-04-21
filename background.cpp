#include "background.h"

void Background::init(Graphics& gfx, const char* filename) {
    texture = gfx.loadTexture(filename);
    scrollX = 0;
}

void Background::update() {
    scrollX += scrollSpeed;
    if (scrollX >= SCREEN_WIDTH) scrollX = 0;
}

void Background::render(Graphics& gfx) {
    SDL_Rect src1 = { scrollX, 0, SCREEN_WIDTH - scrollX, SCREEN_HEIGHT };
    SDL_Rect dst1 = { 0, 0, SCREEN_WIDTH - scrollX, SCREEN_HEIGHT };

    SDL_Rect src2 = { 0, 0, scrollX, SCREEN_HEIGHT };
    SDL_Rect dst2 = { SCREEN_WIDTH - scrollX, 0, scrollX, SCREEN_HEIGHT };

    SDL_RenderCopy(gfx.renderer, texture, &src1, &dst1);
    SDL_RenderCopy(gfx.renderer, texture, &src2, &dst2);
}
