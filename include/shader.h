#pragma once

#ifndef SHADER_H
#define SHADER_H

#include "vectors.h"
#include "objects.h"

double ComputeLighting(
    const Ray &ray_object,
    const Vector3D<double> &Normal,
    int specular
);

#endif