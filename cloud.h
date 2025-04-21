#ifndef CLOUD_H
#define CLOUD_H

#include <SDL.h>
#include <vector>
#include "graphics.h"
#include "defs.h"

struct Cloud {
    float x, y;
    int width, height;
};

class CloudManager {
public:
    void init(Graphics& gfx);
    void update();
    void render(Graphics& gfx);
    void triggerDarkCloud();
    bool isUnderDarkCloud(int x, int y, int w, int h) const;
private:
    std::vector<Cloud> layer1;
    std::vector<Cloud> layer2;

    SDL_Texture* cloudTexture = nullptr;

    // Mây đen sự kiện
    bool darkCloudActive = false;
    float darkCloudX = 0.0f;
    float darkCloudSpeed = 1.0f;
    SDL_Texture* darkCloudTexture = nullptr;
    Uint32 lastDarkCloudTime = 0;
    const Uint32 darkCloudInterval = 15000; // 15s

    const float cloudSpeed1 = 0.3f;
    const float cloudSpeed2 = 0.6f;
    const int maxClouds = 5;
};

#endif
