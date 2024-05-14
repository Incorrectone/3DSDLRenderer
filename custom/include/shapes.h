#pragma once

#ifndef SHAPES_H
#define SHAPES_H

#include "vectors.h"

namespace shapes{
    // A simple sphere
    struct SPHERE{
        VEC::VECTOR3D center;
        double radius;
        VEC::VECTOR3Di color;
        int valid;
        int specular;
    };

    // Initilizes a sphere, with valid key = 1
    SPHERE initSphere(
        VEC::VECTOR3D center,
        double radius,
        VEC::VECTOR3Di color,
        int specular = -1
    );
}

#endif
