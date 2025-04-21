#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "graphics.h"
#include "defs.h"

class Background {
public:
    void init(Graphics& gfx, const char* filename);
    void update();
    void render(Graphics& gfx);

private:
    SDL_Texture* texture = nullptr;
    int scrollX = 0;
    int scrollSpeed = 1;
};

#endif
