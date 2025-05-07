// Placeholder for XiaolinWu.cpp
// Beginner-friendly explanations and calculations included.
// XiaolinWu.cpp
// Simulated anti-aliased line drawing using Xiaolin Wu's algorithm
// Beginner-friendly version using console output

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// Simulated plot function: displays the pixel and its intensity (0.0 to 1.0)
void plot(int x, int y, float brightness) {
    cout << fixed << setprecision(2);
    cout << "Plotting pixel at (" << x << ", " << y << ") with intensity: " << brightness << endl;
}

// Integer part of a float
int ipart(float x) {
    return int(floor(x));
}

// Fractional part of a float
float fpart(float x) {
    return x - floor(x);
}

// Reverse fractional part
float rfpart(float x) {
    return 1.0f - fpart(x);
}

// Xiaolin Wu's algorithm for anti-aliased line
void drawWuLine(float x0, float y0, float x1, float y1) {
    bool steep = fabs(y1 - y0) > fabs(x1 - x0);

    // Swap axes if steep
    if (steep) {
        swap(x0, y0);
        swap(x1, y1);
    }

    // Ensure drawing from left to right
    if (x0 > x1) {
        swap(x0, x1);
        swap(y0, y1);
    }

    float dx = x1 - x0;
    float dy = y1 - y0;
    float gradient = (dx == 0.0f) ? 1.0f : dy / dx;

    // Handle first endpoint
    float xend = round(x0);
    float yend = y0 + gradient * (xend - x0);
    float xgap = rfpart(x0 + 0.5f);
    int xpxl1 = int(xend);
    int ypxl1 = ipart(yend);

    if (steep) {
        plot(ypxl1, xpxl1, rfpart(yend) * xgap);
        plot(ypxl1 + 1, xpxl1, fpart(yend) * xgap);
    } else {
        plot(xpxl1, ypxl1, rfpart(yend) * xgap);
        plot(xpxl1, ypxl1 + 1, fpart(yend) * xgap);
    }

    float intery = yend + gradient;

    // Handle second endpoint
    xend = round(x1);
    yend = y1 + gradient * (xend - x1);
    xgap = fpart(x1 + 0.5f);
    int xpxl2 = int(xend);
    int ypxl2 = ipart(yend);

    // Main loop
    for (int x = xpxl1 + 1; x < xpxl2; x++) {
        if (steep) {
            plot(ipart(intery), x, rfpart(intery));
            plot(ipart(intery) + 1, x, fpart(intery));
        } else {
            plot(x, ipart(intery), rfpart(intery));
            plot(x, ipart(intery) + 1, fpart(intery));
        }
        intery += gradient;
    }

    // Draw second endpoint
    if (steep) {
        plot(ypxl2, xpxl2, rfpart(yend) * xgap);
        plot(ypxl2 + 1, xpxl2, fpart(yend) * xgap);
    } else {
        plot(xpxl2, ypxl2, rfpart(yend) * xgap);
        plot(xpxl2, ypxl2 + 1, fpart(yend) * xgap);
    }
}

// Main function
int main() {
    float x0, y0, x1, y1;

    cout << "Enter starting point (x0 y0): ";
    cin >> x0 >> y0;
    cout << "Enter ending point (x1 y1): ";
    cin >> x1 >> y1;

    drawWuLine(x0, y0, x1, y1);

    return 0;
}
