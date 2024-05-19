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

    VEC::VECTOR3Di addVectors(
        VEC::VECTOR3Di vector1, 
        VEC::VECTOR3Di vector2,
        int isColor = 0
    );

    VEC::VECTOR3D mscalarVector(
        double scalar, 
        VEC::VECTOR3D vector
    );

    VEC::VECTOR3Di mscalarVector(
        double scalar, 
        VEC::VECTOR3Di vector,
        int isColor = 0
    );

    double vectorDotProduct(
        VEC::VECTOR3D vector1, 
        VEC::VECTOR3D vector2
    );  

    double absoluteValue(
        VEC::VECTOR3D vector
    );

    VEC::VECTOR3D ReflectedRay(
        VEC::VECTOR3D Normal,
        VEC::VECTOR3D VectortobeReflected
    );
}


#endif