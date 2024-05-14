#pragma once

#ifndef VECTORMATH_H
#define VECTORMATH_H

#include "vectors.h"

namespace vectormath{
    VEC::VECTOR3D subtractVectors(
        VEC::VECTOR3D vector1, 
        VEC::VECTOR3D vector2
    );

    VEC::VECTOR3D addVectors(
        VEC::VECTOR3D vector1, 
        VEC::VECTOR3D vector2
    );

    VEC::VECTOR3D mscalarVector(
        double scalar, 
        VEC::VECTOR3D vector
    );

    VEC::VECTOR3Di mscalarVector(
        double scalar, 
        VEC::VECTOR3Di vector
    );

    double vectorDotProduct(
        VEC::VECTOR3D vector1, 
        VEC::VECTOR3D vector2
    );  

    double absoluteValue(
        VEC::VECTOR3D vector
    );
}


#endif