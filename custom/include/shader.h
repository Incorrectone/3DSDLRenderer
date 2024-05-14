#pragma once

#ifndef SHADER_H
#define SHADER_H

#include "vectors.h"

namespace shader{
    typedef struct light_S{
        char type;
        double intensity;
        VEC::VECTOR3D direction;
        VEC::VECTOR3Di color;
        int valid;
    } Light;

    Light initLight(
        char type, 
        double intensity,   
        VEC::VECTOR3D direction,
        VEC::VECTOR3Di color
    );

    double ComputeLighting(
        VEC::VECTOR3D Point,
        VEC::VECTOR3D Normal,
        Light lightList[],
        int numberofLights
    );
}

#endif