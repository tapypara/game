#ifndef LOGIC_H
#define LOGIC_H

#include <vector>
#include <SDL.h>
#include <string>
void startStroke();
void addPointFromMouse();
char endStrokeAndCheckMatch(const std::vector<SDL_Point>& stroke);
std::string convertToDirectionString(const std::vector<SDL_Point>& points);
char angleToDirection(float angleDeg);
void interpolateAndAdd(SDL_Point last, SDL_Point next);
extern std::vector<SDL_Point> currentStroke;

#endif
