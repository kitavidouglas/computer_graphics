// Placeholder for Midpoint.cpp
// Beginner-friendly explanations and calculations included.
// Midpoint.cpp
// This program calculates the midpoint between two points in 2D space
// Author: [Your Name]
// Date: [Today’s Date]

#include <iostream>
using namespace std;

int main() {
    // Declare variables for the coordinates of the two points
    double x1, y1, x2, y2;

    // Prompt user to enter coordinates for the first point
    cout << "Enter x-coordinate of the first point (x1): ";
    cin >> x1;
    cout << "Enter y-coordinate of the first point (y1): ";
    cin >> y1;

    // Prompt user to enter coordinates for the second point
    cout << "Enter x-coordinate of the second point (x2): ";
    cin >> x2;
    cout << "Enter y-coordinate of the second point (y2): ";
    cin >> y2;

    // Calculate the midpoint using the midpoint formula:
    // midpoint_x = (x1 + x2) / 2
    // midpoint_y = (y1 + y2) / 2
    double midpoint_x = (x1 + x2) / 2.0;
    double midpoint_y = (y1 + y2) / 2.0;

    // Display the result
    cout << "\nThe midpoint between (" << x1 << ", " << y1 << ") and ("
         << x2 << ", " << y2 << ") is: (" 
         << midpoint_x << ", " << midpoint_y << ")\n";

    return 0;
}
