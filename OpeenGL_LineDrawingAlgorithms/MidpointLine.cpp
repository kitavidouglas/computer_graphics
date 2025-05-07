// Placeholder for MidpointLine.cpp
// Beginner-friendly explanations and calculations included.
// MidpointLine.cpp
// Beginner-friendly implementation of the Midpoint Line Drawing Algorithm

#include <iostream>
#include <cmath>
using namespace std;

// Function to simulate plotting a point (replace with actual graphics code if needed)
void plot(int x, int y) {
    cout << "Plotting pixel at (" << x << ", " << y << ")" << endl;
}

// Midpoint Line Drawing Algorithm
void drawMidpointLine(int x0, int y0, int x1, int y1) {
    cout << "\n--- Midpoint Line Drawing ---\n";

    // Calculate differences
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    // Determine the direction of steps
    int sx = (x1 >= x0) ? 1 : -1;
    int sy = (y1 >= y0) ? 1 : -1;

    int x = x0;
    int y = y0;

    // For shallow slope (|m| <= 1)
    if (dx >= dy) {
        int d = 2 * dy - dx;  // Decision parameter
        int incrE = 2 * dy;
        int incrNE = 2 * (dy - dx);

        plot(x, y);  // First point

        while (x != x1) {
            x += sx;
            if (d <= 0) {
                d += incrE;
            } else {
                y += sy;
                d += incrNE;
            }
            plot(x, y);
        }
    }
    // For steep slope (|m| > 1)
    else {
        int d = 2 * dx - dy;
        int incrN = 2 * dx;
        int incrNE = 2 * (dx - dy);

        plot(x, y);

        while (y != y1) {
            y += sy;
            if (d <= 0) {
                d += incrN;
            } else {
                x += sx;
                d += incrNE;
            }
            plot(x, y);
        }
    }
}

// Main function
int main() {
    int x0, y0, x1, y1;

    cout << "Enter starting point (x0 y0): ";
    cin >> x0 >> y0;
    cout << "Enter ending point (x1 y1): ";
    cin >> x1 >> y1;

    drawMidpointLine(x0, y0, x1, y1);

    return 0;
}
