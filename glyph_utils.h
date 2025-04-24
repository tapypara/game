// glyph_utils.h
#ifndef GLYPH_UTILS_H
#define GLYPH_UTILS_H

#include <vector>
#include <limits>
#include <cmath>

struct Point {
    float x, y;
};

std::vector<Point> resample(const std::vector<Point>& input, int n);
void normalize(std::vector<Point>& points);
float compareGlyphs(const std::vector<Point>& a, const std::vector<Point>& b);

#endif // GLYPH_UTILS_H
