// Placeholder for Bresenham.cpp
// Beginner-friendly explanations and calculations included.
// Bresenham.cpp
// Implementation of Bresenham’s Line Drawing Algorithm
// Author: [Your Name]
// Date: [Today’s Date]

// This program uses simple terminal output to simulate line drawing on a grid.
// In a graphics application, you would typically use a graphics library like OpenGL or SDL.

#include <iostream>
#include <cmath>
using namespace std;

// Function to plot a point (in real graphics, this would draw a pixel)
void plotPoint(int x, int y) {
    cout << "(" << x << ", " << y << ") ";
}

// Bresenham's Line Drawing Algorithm
// Draws a line from (x1, y1) to (x2, y2)
void drawLine(int x1, int y1, int x2, int y2) {
    // Calculate the differences in x and y
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    // Decide the direction of increment
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    // Initialize the error term
    int err = dx - dy;

    while (true) {
        plotPoint(x1, y1);  // Plot the current point

        // Check if the end point is reached
        if (x1 == x2 && y1 == y2) break;

        // Calculate error and decide the next point
        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

int main() {
    int x1, y1, x2, y2;

    // Prompt user to enter the coordinates of the start and end point
    cout << "Enter the starting point (x1 y1): ";
    cin >> x1 >> y1;

    cout << "Enter the ending point (x2 y2): ";
    cin >> x2 >> y2;

    cout << "\nDrawing line from (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << "):\n";
    drawLine(x1, y1, x2, y2);
    cout << "\n";

    return 0;
}
