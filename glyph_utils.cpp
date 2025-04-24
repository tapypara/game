// glyph_utils.cpp
#include "glyph_utils.h"
#include <algorithm>
using namespace std;

vector<Point> resample(const vector<Point>& input, int n) {
    if (input.empty()) return {};
    if (input.size() == 1) return vector<Point>(n, input[0]);

    vector<float> dists;
    float totalLength = 0;
    for (size_t i = 1; i < input.size(); ++i) {
        float dx = input[i].x - input[i - 1].x;
        float dy = input[i].y - input[i - 1].y;
        float dist = sqrt(dx * dx + dy * dy);
        dists.push_back(dist);
        totalLength += dist;
    }

    float segmentLength = totalLength / (n - 1);
    vector<Point> result;
    result.push_back(input[0]);
    float distSoFar = 0;

    size_t i = 1;
    Point prev = input[0];
    while (i < input.size()) {
        float dx = input[i].x - prev.x;
        float dy = input[i].y - prev.y;
        float dist = sqrt(dx * dx + dy * dy);

        if ((distSoFar + dist) >= segmentLength) {
            float t = (segmentLength - distSoFar) / dist;
            Point newPoint = {
                prev.x + t * dx,
                prev.y + t * dy
            };
            result.push_back(newPoint);
            prev = newPoint;
            distSoFar = 0;
        } else {
            distSoFar += dist;
            prev = input[i];
            ++i;
        }
    }

    while (result.size() < static_cast<size_t>(n)) {
        result.push_back(input.back());
    }

    return result;
}

void normalize(vector<Point>& points) {
    if (points.empty()) return;

    float minX = numeric_limits<float>::max();
    float minY = numeric_limits<float>::max();
    float maxX = numeric_limits<float>::lowest();
    float maxY = numeric_limits<float>::lowest();

    for (const auto& p : points) {
        minX = min(minX, p.x);
        minY = min(minY, p.y);
        maxX = max(maxX, p.x);
        maxY = max(maxY, p.y);
    }

    float width = maxX - minX;
    float height = maxY - minY;

    for (auto& p : points) {
        p.x = (width > 0) ? (p.x - minX) / width : 0.5f;
        p.y = (height > 0) ? (p.y - minY) / height : 0.5f;
    }
}

float compareGlyphs(const vector<Point>& a, const vector<Point>& b) {
    if (a.size() != b.size()) return numeric_limits<float>::max();
    float sum = 0.0f;
    for (size_t i = 0; i < a.size(); ++i) {
        float dx = a[i].x - b[i].x;
        float dy = a[i].y - b[i].y;
        sum += sqrt(dx * dx + dy * dy);
    }
    return sum / static_cast<float>(a.size());
}