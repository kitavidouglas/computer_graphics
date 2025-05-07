// Placeholder for DDA.cpp
// Beginner-friendly explanations and calculations included.
// DDA.cpp
// Draws a line using DDA (Digital Differential Analyzer) algorithm
// Outputs points to the console for a simple demonstration

#include <iostream>
#include <cmath>
using namespace std;

// Function to plot the line using DDA Algorithm
void drawLine(int x0, int y0, int x1, int y1) {
    cout << "Drawing line from (" << x0 << ", " << y0 << ") to ("
         << x1 << ", " << y1 << "):\n";

    // Calculate differences
    int dx = x1 - x0;  // difference in x-coordinates
    int dy = y1 - y0;  // difference in y-coordinates

    // Determine the number of steps required for drawing the line
    int steps = max(abs(dx), abs(dy));  // greater of dx or dy for equal spacing of points

    // Calculate the increment for each step
    float xIncrement = float(dx) / steps;
    float yIncrement = float(dy) / steps;

    // Starting point
    float x = x0;
    float y = y0;

    // Loop through each step and plot the points
    for (int i = 0; i <= steps; i++) {
        cout << "(" << round(x) << ", " << round(y) << ")\n";  // Round to nearest integer
        x += xIncrement;  // increment x by xIncrement
        y += yIncrement;  // increment y by yIncrement
    }
}

// Main function to test the algorithm
int main() {
    int x_start, y_start, x_end, y_end;

    // User input for starting and ending points
    cout << "Enter starting point (x0 y0): ";
    cin >> x_start >> y_start;

    cout << "Enter ending point (x1 y1): ";
    cin >> x_end >> y_end;

    // Call the DDA function to draw the line
    drawLine(x_start, y_start, x_end, y_end);

    return 0;
}
