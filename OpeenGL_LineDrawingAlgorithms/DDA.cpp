// DDA.cpp
// Advanced DDA line-drawing tool with rotation and file output
// Author: Kitavi Douglas Kimani
// Date: 2025-05-07

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <stdexcept>
using namespace std;

// Virtual canvas
class Canvas {
    int width, height;
    vector<string> grid;
    char bg;

public:
    Canvas(int w, int h, char bgSym = '.') 
      : width(w), height(h), bg(bgSym), grid(h, string(w, bgSym)) {}

    void plot(int x, int y, char sym = '#') {
        if (x>=0 && x<width && y>=0 && y<height)
            grid[height - 1 - y][x] = sym;
    }

    void clear() {
        for (auto &row : grid) row.assign(width, bg);
    }

    void display() const {
        for (auto &row : grid) {
            for (char c : row) cout << c << ' ';
            cout << '\n';
        }
    }

    void save(const string &filename) const {
        ofstream ofs(filename);
        if (!ofs) throw runtime_error("Cannot open file: " + filename);
        for (auto &row : grid) {
            for (char c : row) ofs << c << ' ';
            ofs << '\n';
        }
    }
};

// DDA drawer
class DDALineDrawer {
    Canvas &canvas;
public:
    DDALineDrawer(Canvas &c) : canvas(c) {}

    void draw(int x0, int y0, int x1, int y1, char sym='#') {
        int dx = x1 - x0, dy = y1 - y0;
        int steps = max(abs(dx), abs(dy));
        if (steps == 0) { canvas.plot(x0,y0,sym); return; }

        float xInc = float(dx)/steps;
        float yInc = float(dy)/steps;
        float x = x0, y = y0;

        for (int i = 0; i <= steps; ++i) {
            canvas.plot(int(round(x)), int(round(y)), sym);
            x += xInc;  y += yInc;
        }
    }
};

// 2D point
struct Point {
    float x, y;
};

// Compute centroid of polygon
Point centroid(const vector<Point> &pts) {
    float cx = 0, cy = 0;
    for (auto &p : pts) { cx += p.x; cy += p.y; }
    int n = pts.size();
    return {cx/n, cy/n};
}

// Rotate a point about origin
Point rotatePt(const Point &p, float angRad, const Point &origin) {
    float s = sin(angRad), c = cos(angRad);
    float x = p.x - origin.x, y = p.y - origin.y;
    return {
      origin.x + x * c - y * s,
      origin.y + x * s + y * c
    };
}

// Draw a polygon (closed shape)
void drawPolygon(DDALineDrawer &drawer, const vector<Point> &pts, char sym) {
    int n = pts.size();
    for (int i = 0; i < n; ++i) {
        auto &A = pts[i], &B = pts[(i+1)%n];
        drawer.draw(int(round(A.x)), int(round(A.y)),
                    int(round(B.x)), int(round(B.y)), sym);
    }
}

int main() {
    const int W = 60, H = 30;
    Canvas canvasOrig(W,H), canvasRot(W,H);
    DDALineDrawer drawerOrig(canvasOrig), drawerRot(canvasRot);

    // Sample polygon: a pentagon
    vector<Point> polygon = {
        {10, 5}, {20, 5}, {25, 15}, {15, 25}, {5, 15}
    };

    // Compute centroid and set rotation angle
    Point cen = centroid(polygon);
    float angleDegrees;
    cout << "Enter rotation angle (degrees): ";
    cin >> angleDegrees;
    float angRad = angleDegrees * M_PI / 180.0f;

    // Draw original
    drawPolygon(drawerOrig, polygon, '*');

    // Compute rotated vertices
    vector<Point> rotated;
    for (auto &p : polygon)
        rotated.push_back(rotatePt(p, angRad, cen));

    // Draw rotated
    drawPolygon(drawerRot, rotated, '#');

    // Display side by side
    cout << "\nOriginal Polygon:\n";
    canvasOrig.display();
    cout << "\nRotated Polygon (" << angleDegrees << "°):\n";
    canvasRot.display();

    // Save to files
    canvasOrig.save("original_shape.txt");
    canvasRot.save("rotated_shape.txt");
    cout << "\nSaved frames to original_shape.txt and rotated_shape.txt\n";

    return 0;
}
