#include "logic.h"
#include <cmath>
using namespace std;
std::vector<SDL_Point> currentStroke;
std::vector<SDL_Point> drawingPoints;
char angleToDirection(float angleDeg) {
    if (angleDeg < 0) angleDeg += 360.0f;
    if ((angleDeg >= 315 || angleDeg < 45))   return 'R';
    if (angleDeg >= 45 && angleDeg < 135)     return 'D';
    if (angleDeg >= 135 && angleDeg < 225)    return 'L';
    if (angleDeg >= 225 && angleDeg < 315)    return 'U';
    return '?';
}
string convertToDirectionString(const std::vector<SDL_Point>& points) {
    char lastDir = '?';
    string result;
    for (size_t i = 1; i < points.size(); ++i) {
        int dx = points[i].x - points[i - 1].x;
        int dy = points[i].y - points[i - 1].y;
        float distance = sqrt(dx * dx + dy * dy);
        if (distance < 10) continue;
        float angleRad = std::atan2(dy, dx);
        float angleDeg = angleRad * (180.0f / M_PI);
        char dir = angleToDirection(angleDeg);

        if (dir != lastDir) {
            result += dir;
            lastDir = dir;
        }
    }
    return result;
}
void interpolateAndAdd(SDL_Point last, SDL_Point next) {
    int dx = next.x - last.x;
    int dy = next.y - last.y;
    int steps = std::max(abs(dx), abs(dy));
    for (int i = 1; i < steps; ++i) {
        float t = (float)i / steps;
        int xi = last.x + t * dx;
        int yi = last.y + t * dy;
        drawingPoints.push_back({xi, yi});
    }
}
void startStroke() {
    currentStroke.clear();
}
void addPointFromMouse() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    currentStroke.push_back({x, y});
    if (drawingPoints.empty() || (abs(x - drawingPoints.back().x) + abs(y - drawingPoints.back().y)) >= 3) {
        if (!currentStroke.empty()) {
            interpolateAndAdd(drawingPoints.back(), {x, y});
        }
        drawingPoints.push_back({x, y});
    }
}
char endStrokeAndCheckMatch(const vector<SDL_Point>& stroke) {
    string a = convertToDirectionString(stroke);
    if (a.length() >= 5 && a.substr(0,6) == "DUDUDU") return '#';
    if (a.length() >= 2 && a[0] == 'D' && a[1] == 'U') return 'V';
    if (a.length() >= 3 && ((a[0] == 'R' && a[1] == 'D') || (a[1] == 'L' && a[2] == 'R'))) return 'Z';
    if (a.length() == 1 && (a[0] == 'U' || a[0] == 'D')) return 'I';
    if (a.length() >= 7 && a[0] == 'R' && a[a.length()-1] == 'R') {
        int countdownonce = 0;
        for (int i = 2; i < a.length() - 2; i++) {
            if (a[i] == 'D') countdownonce++;
            if (countdownonce == 1 && i == a.length() - 3) return 'F';
        }
    }
    if (a.length() >= 4) {
        int has_L = 0, has_D = 0, has_R = 0, has_U = 0;
        if (a.length() >= 7 && a[0] == 'U' && a[a.length() - 1] == 'D') {
            int countaccept = 0;
            for (int i = 2; i < a.length() - 2; i++) {
                if (a[i] == 'R') countaccept++;
                if (countaccept == 1 && i == a.length() - 3) return 'P';
            }
        }
        for (int i = 0; i < a.length(); i++) {
            if ((a[i] == 'L') && has_L == 0) has_L = i + 1;
            if ((a[i] == 'D') && has_D == 0) has_D = i + 1;
            if ((a[i] == 'R') && has_R == 0) has_R = i + 1;
            if ((a[i] == 'U') && has_U == 0) has_U = i + 1;
            if (has_L * has_D * has_R * has_U) return 'O';
        }
    }

    return 'x';
}
