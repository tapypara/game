#ifndef LOGIC_H
#define LOGIC_H

#include <vector>
#include <SDL.h>
#include <string>

std::string convertToDirectionString(const std::vector<SDL_Point>& points);
char angleToDirection(float angleDeg);

#endif // LOGIC_H

