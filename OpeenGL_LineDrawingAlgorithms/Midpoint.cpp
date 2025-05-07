// Midpoint.cpp
// Advanced Geometry Tool for midpoint, distance, and reflection calculations in 2D/3D
// Author: Kitavi Douglas Kimani
// Date: 2025-05-07

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <stdexcept>
using namespace std;

// Define a Point class with 3D support
class Point {
public:
    double x, y, z;

    Point(double x=0, double y=0, double z=0) : x(x), y(y), z(z) {}

    // Operator overload for midpoint
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y, z + other.z);
    }

    Point operator/(double val) const {
        return Point(x / val, y / val, z / val);
    }

    // Euclidean distance between two points
    double distanceTo(const Point& other) const {
        return sqrt(pow(x - other.x, 2) +
                    pow(y - other.y, 2) +
                    pow(z - other.z, 2));
    }

    // Reflect point across the midpoint
    Point symmetricReflection(const Point& mid) const {
        return Point(2 * mid.x - x, 2 * mid.y - y, 2 * mid.z - z);
    }

    void display(bool showZ = false) const {
        cout << fixed << setprecision(2)
             << "(" << x << ", " << y;
        if (showZ) cout << ", " << z;
        cout << ")";
    }
};

// Function to process multiple point pairs
void processPoints(const vector<pair<Point, Point>>& pointPairs, bool is3D = false) {
    cout << left << setw(25) << "Point A"
         << setw(25) << "Point B"
         << setw(25) << "Midpoint"
         << setw(15) << "Distance"
         << setw(25) << "Reflection of A (w.r.t. Mid)" << "\n";

    cout << string(115, '-') << "\n";

    for (const auto& pair : pointPairs) {
        const Point& A = pair.first;
        const Point& B = pair.second;

        Point midpoint = (A + B) / 2.0;
        double dist = A.distanceTo(B);
        Point reflectedA = A.symmetricReflection(midpoint);

        A.display(is3D); cout << setw(15);
        cout << "   ";
        B.display(is3D); cout << setw(15);
        cout << "   ";
        midpoint.display(is3D); cout << setw(15);
        cout << "   ";
        cout << setw(10) << dist << "   ";
        reflectedA.display(is3D);
        cout << "\n";
    }
}

int main() {
    try {
        int numPairs;
        bool is3D;
        cout << "Enter number of point pairs: ";
        cin >> numPairs;

        cout << "Enable 3D mode? (1 for yes, 0 for no): ";
        cin >> is3D;

        vector<pair<Point, Point>> pointPairs;

        for (int i = 0; i < numPairs; ++i) {
            double x1, y1, z1 = 0, x2, y2, z2 = 0;

            cout << "\nPoint Pair #" << i + 1 << "\n";
            cout << "Enter coordinates for Point A (x y";
            if (is3D) cout << " z";
            cout << "): ";
            cin >> x1 >> y1;
            if (is3D) cin >> z1;

            cout << "Enter coordinates for Point B (x y";
            if (is3D) cout << " z";
            cout << "): ";
            cin >> x2 >> y2;
            if (is3D) cin >> z2;

            Point A(x1, y1, z1);
            Point B(x2, y2, z2);
            pointPairs.push_back({A, B});
        }

        cout << "\nCalculating midpoints, distances, and symmetric reflections...\n\n";
        processPoints(pointPairs, is3D);

    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
    }

    return 0;
}
