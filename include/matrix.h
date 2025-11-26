#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include "vectors.h"

void rotationMatrix(
    const Vector3D<double>& a, 
    double m[3][3]
);

#endif