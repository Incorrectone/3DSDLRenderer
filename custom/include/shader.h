#pragma once

#ifndef SHADER_H
#define SHADER_H

#include "vectors.h"
#include "shapes.h"

namespace shader{
    struct Light{
        char type;
        double intensity;
        VEC::VECTOR3D direction;
        VEC::VECTOR3D color;
        int valid;
    };

    Light initLight(
        char type, 
        double intensity,   
        VEC::VECTOR3D direction,
        VEC::VECTOR3D color
    );

    double ComputeLighting(
        VEC::VECTOR3D Point,
        VEC::VECTOR3D Normal,
        VEC::VECTOR3D directiontoViewport,
        int specular,
        Light lightList[],
        int numberofLights,
        shapes::SPHERE objectList[],
        int numberofObjects
    );
}

#endif