#pragma once

#ifndef SHADER_H
#define SHADER_H

#include "vectors.h"
#include "objects.h"

double ComputeLighting(
    Vector3D<double> Point,
    Vector3D<double> Normal,
    Vector3D<double> directiontoViewport,
    int specular
);

#endif