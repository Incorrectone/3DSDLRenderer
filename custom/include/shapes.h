#pragma once

#ifndef SHAPES_H
#define SHAPES_H

#include "vectors.h"

namespace shapes{
    // A simple sphere
    typedef struct SPHERE_S {
        VEC::VECTOR3D center;
        double radius;
        VEC::VECTOR3Di color;
        int valid;
    } SPHERE;

    // Initilizes a sphere, with valid key = 1
    SPHERE initSphere(
        VEC::VECTOR3D center,
        double radius,
        VEC::VECTOR3Di color
    );
}

#endif
