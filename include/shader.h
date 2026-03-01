#pragma once

#ifndef SHADER_H
#define SHADER_H

#include "vectors.h"
#include "objects.h"

double ComputeLighting(
    const Vector3D<double> &Point,
    const Vector3D<double> &Normal,
    const Vector3D<double> &directiontoViewport,
    int specular
);

#endif