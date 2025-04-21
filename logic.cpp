#include "logic.h"
#include <cmath>

// Chuyển góc thành ký hiệu hướng
char angleToDirection(float angleDeg) {
    if (angleDeg < 0) angleDeg += 360.0f;

    if (angleDeg >= 337.5f || angleDeg < 22.5f)   return 'R';
    if (angleDeg >= 22.5f  && angleDeg < 67.5f)   return 'E'; // Down-Right
    if (angleDeg >= 67.5f  && angleDeg < 112.5f)  return 'D';
    if (angleDeg >= 112.5f && angleDeg < 157.5f)  return 'C'; // Down-Left
    if (angleDeg >= 157.5f && angleDeg < 202.5f)  return 'L';
    if (angleDeg >= 202.5f && angleDeg < 247.5f)  return 'A'; // Up-Left
    if (angleDeg >= 247.5f && angleDeg < 292.5f)  return 'U';
    if (angleDeg >= 292.5f && angleDeg < 337.5f)  return 'B'; // Up-Right

    return '?'; // Không xác định
}

// Chuyển vector điểm → chuỗi hướng
std::string convertToDirectionString(const std::vector<SDL_Point>& points) {
    if (points.size() < 2) return "";

    std::string result;
    char lastDir = '\0';

    for (size_t i = 1; i < points.size(); ++i) {
        int dx = points[i].x - points[i - 1].x;
        int dy = points[i].y - points[i - 1].y;

        // Bỏ nhiễu nếu đoạn quá ngắn
        if (dx * dx + dy * dy < 16) continue; // dưới 4px

        float angleRad = std::atan2(dy, dx);
        float angleDeg = angleRad * (180.0f / M_PI);
        char dir = angleToDirection(angleDeg);

        // Bỏ hướng trùng liên tiếp
        if (dir != lastDir) {
            result += dir;
            lastDir = dir;
        }
    }

    return result;
}
