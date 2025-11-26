#include "vectors.h"

#include "matrix.h"

#include <cmath>

void rotationMatrix(const Vector3D<double>& a, double m[3][3]) {
    // https://en.wikipedia.org/wiki/Rotation_matrix
    double sa = std::sin(a.z);  // yaw
    double ca = std::cos(a.z);
    double sb = std::sin(a.y); // pitch
    double cb = std::cos(a.y);
    double sc = std::sin(a.x);   // roll
    double cc = std::cos(a.x);

    // Row 1
    m[0][0] = ca * cb;
    m[0][1] = ca * sb * sc - sa * cc;
    m[0][2] = ca * sb * cc + sa * sc;

    // Row 2
    m[1][0] = sa * cb;
    m[1][1] = sa * sb * sc + ca * cc;
    m[1][2] = sa * sb * cc - ca * sc;

    // Row 3
    m[2][0] = - sb;
    m[2][1] = cb * sc;
    m[2][2] = cb * cc;
}