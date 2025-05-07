// Placeholder for GuptaSproull.cpp
// Beginner-friendly explanations and calculations included.
// GuptaSproull.cpp
// Simulates Gupta-Sproull anti-aliased line drawing algorithm
// Beginner-friendly with console output and basic intensity estimation

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Simulated plot function that outputs point and its intensity
void plot(int x, int y, float intensity) {
    cout << fixed << setprecision(2);
    cout << "Pixel at (" << x << ", " << y << ") with intensity: " << intensity << endl;
}

// Function to compute intensity based on distance
float getIntensity(float distance, float lineWidth = 1.0f) {
    float maxDistance = 1.5f * lineWidth;
    if (distance >= maxDistance)
        return 0.0f;
    return max(0.0f, 1.0f - (distance / maxDistance));
}

// Gupta-Sproull line drawing (assumes line is shallow: |dy| < |dx|)
void drawLine(int x0, int y0, int x1, int y1) {
    cout << "Drawing anti-aliased line from (" << x0 << ", " << y0 << ") to (" << x1 << ", " << y1 << "):\n";

    int dx = x1 - x0;
    int dy = y1 - y0;

    int sx = (dx >= 0) ? 1 : -1;
    int sy = (dy >= 0) ? 1 : -1;

    dx = abs(dx);
    dy = abs(dy);

    bool steep = dy > dx;
    if (steep) {
        swap(x0, y0);
        swap(x1, y1);
        swap(dx, dy);
        swap(sx, sy);
    }

    float gradient = float(dy) / dx;
    float intery = y0 + gradient;

    int x = x0;
    int y = y0;

    plot(steep ? y : x, steep ? x : y, 1.0f);  // First pixel (full intensity)

    for (int i = 1; i <= dx; i++) {
        x += sx;
        float d = intery - floor(intery);
        int baseY = int(intery);
        
        // Simulate brightness (closer to center line = higher intensity)
        plot(steep ? baseY : x, steep ? x : baseY, getIntensity(1.0f - d));
        plot(steep ? baseY + 1 : x, steep ? x : baseY + 1, getIntensity(d));

        intery += gradient;
    }

    plot(steep ? y1 : x1, steep ? x1 : y1, 1.0f);  // Last pixel
}

// Main function
int main() {
    int x_start, y_start, x_end, y_end;

    cout << "Enter starting point (x0 y0): ";
    cin >> x_start >> y_start;

    cout << "Enter ending point (x1 y1): ";
    cin >> x_end >> y_end;

    drawLine(x_start, y_start, x_end, y_end);

    return 0;
}
