// Bresenham.cpp
// Advanced implementation using Object-Oriented Programming and modularity
// Draws multiple lines from the center outward to form a star/radial pattern.

#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
using namespace std;

// Canvas dimensions (for virtual grid)
const int WIDTH = 40;
const int HEIGHT = 20;

// Canvas class to simulate plotting in a 2D matrix
class Canvas {
private:
    vector<vector<char>> grid;

public:
    Canvas(int width, int height) {
        grid.resize(height, vector<char>(width, '.'));  // initialize with dots
    }

    void plotPoint(int x, int y, char symbol = '*') {
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            grid[HEIGHT - y - 1][x] = symbol;  // invert y for correct display
        }
    }

    void display() {
        for (const auto& row : grid) {
            for (char c : row) {
                cout << c << " ";
            }
            cout << endl;
        }
    }

    void clear() {
        for (auto& row : grid) {
            fill(row.begin(), row.end(), '.');
        }
    }
};

// LineDrawer class encapsulates Bresenham's algorithm
class LineDrawer {
private:
    Canvas& canvas;

public:
    LineDrawer(Canvas& c) : canvas(c) {}

    void drawLine(int x1, int y1, int x2, int y2, char symbol = '*') {
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;
        int err = dx - dy;

        while (true) {
            canvas.plotPoint(x1, y1, symbol);

            if (x1 == x2 && y1 == y2) break;

            int e2 = 2 * err;
            if (e2 > -dy) { err -= dy; x1 += sx; }
            if (e2 < dx)  { err += dx; y1 += sy; }
        }
    }
};

// Function to draw a radial star from center with N rays
void drawRadialStar(LineDrawer& drawer, int cx, int cy, int rays) {
    double angleStep = 360.0 / rays;

    for (int i = 0; i < rays; ++i) {
        double angle = angleStep * i * M_PI / 180.0;
        int x = cx + static_cast<int>(cos(angle) * 18);  // radius ~18
        int y = cy + static_cast<int>(sin(angle) * 9);   // aspect ratio adjust

        drawer.drawLine(cx, cy, x, y, '#');
    }
}

// Main program
int main() {
    try {
        Canvas canvas(WIDTH, HEIGHT);
        LineDrawer drawer(canvas);

        int centerX = WIDTH / 2;
        int centerY = HEIGHT / 2;
        int numRays;

        cout << "Enter number of rays for the radial star (e.g., 12 or 24): ";
        cin >> numRays;
        if (numRays <= 0 || numRays > 360) throw invalid_argument("Invalid number of rays.");

        drawRadialStar(drawer, centerX, centerY, numRays);

        cout << "\nRadial star pattern:\n";
        canvas.display();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
