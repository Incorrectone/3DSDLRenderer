#pragma once

#ifndef SHAPES_H
#define SHAPES_H

#include "vectors.h"

namespace shapes{
    // A simple sphere
    struct SPHERE{
        VEC::VECTOR3D center;
        double radius;
        VEC::VECTOR3D color;
        int specular;
        double reflective;
        char type;
        int valid;
    };

    // Initilizes a sphere, with valid key = 1
    SPHERE initSphere(
        VEC::VECTOR3D center,
        double radius,
        VEC::VECTOR3D color,
        int specular = -1,
        double reflective = 0.5
    );

    struct PLANE{
        VEC::VECTOR3D Normal;
        double rh;
        VEC::VECTOR3D color;
        int specular;
        double reflective;
        char type;
        int valid;
    };
    
    PLANE initPlane(
        VEC::VECTOR3D Normal,
        double d,
        VEC::VECTOR3D color,
        int specular = -1,
        double reflective = 0.5
    );

    struct returnType{
        SPHERE object;
        double closest_intersection;
    };
}

#endif
