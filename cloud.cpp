#include "cloud.h"
#include <cstdlib>

void CloudManager::init(Graphics& gfx) {
    cloudTexture = gfx.loadTexture("assets/cloud.png");
    darkCloudTexture = gfx.loadTexture("assets/darkcloud.png");

    for (int i = 0; i < maxClouds; ++i) {
        Cloud c1 = { (float)(rand() % SCREEN_WIDTH), (float)(rand() % 200 + 50), 100, 40 };
        layer1.push_back(c1);
        Cloud c2 = { (float)(rand() % SCREEN_WIDTH), (float)(rand() % 300 + 150), 120, 50 };
        layer2.push_back(c2);
    }

    lastDarkCloudTime = SDL_GetTicks();
}

void CloudManager::update() {
    Uint32 now = SDL_GetTicks();

    for (auto it = layer1.begin(); it != layer1.end();) {
        it->x -= cloudSpeed1;
        if (it->x + it->width < 0) {
            it = layer1.erase(it);
        } else {
            ++it;
        }
    }
    if (layer1.size() < maxClouds) {
        Cloud c = { (float)(SCREEN_WIDTH + rand() % 200), (float)(rand() % 200 + 50), 100, 40 };
        layer1.push_back(c);
    }

    for (auto it = layer2.begin(); it != layer2.end();) {
        it->x -= cloudSpeed2;
        if (it->x + it->width < 0) {
            it = layer2.erase(it);
        } else {
            ++it;
        }
    }
    if (layer2.size() < maxClouds) {
        Cloud c = { (float)(SCREEN_WIDTH + rand() % 200), (float)(rand() % 300 + 150), 120, 50 };
        layer2.push_back(c);
    }

    if (darkCloudActive) {
        darkCloudX -= darkCloudSpeed;
        if (darkCloudX + SCREEN_WIDTH * 2 < 0) {
            darkCloudActive = false;
            lastDarkCloudTime = now;
        }
    } else if (now - lastDarkCloudTime >= darkCloudInterval) {
        if (rand() % 2 == 0) {
            triggerDarkCloud();
        } else {
            lastDarkCloudTime = now;
        }
    }
}

void CloudManager::render(Graphics& gfx) {
    // Nền màu xanh nước
    SDL_SetRenderDrawColor(gfx.renderer, 135, 206, 235, 255);
    SDL_RenderClear(gfx.renderer);

    for (const auto& cloud : layer1) {
        gfx.renderTexture(cloudTexture, (int)cloud.x, (int)cloud.y);
    }

    for (const auto& cloud : layer2) {
        gfx.renderTexture(cloudTexture, (int)cloud.x, (int)cloud.y);
    }

    if (darkCloudActive && darkCloudTexture) {
        gfx.renderTexture(darkCloudTexture, (int)darkCloudX, 0);
    }
}

void CloudManager::triggerDarkCloud() {
    darkCloudActive = true;
    darkCloudX = SCREEN_WIDTH;
}

bool CloudManager::isUnderDarkCloud(int x, int y, int w, int h) const {
    if (!darkCloudActive) return false;
    SDL_Rect cloudRect = { (int)darkCloudX, 0, SCREEN_WIDTH * 2, 150 };
    SDL_Rect objRect = { x, y, w, h };
    SDL_Rect result;
    return SDL_IntersectRect(&cloudRect, &objRect, &result);
}
