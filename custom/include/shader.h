#pragma once

#ifndef SHADER_H
#define SHADER_H

#include "vectors.h"
#include "shapes.h"
    
struct Light{
    char type;
    double intensity;
    Vector3D<double> direction;
    Vector3D<int> color;
    int valid;

Light(char TYPE, double INTENSITY ,Vector3D<double> DIRECTION, Vector3D<double> COLOR) : type{TYPE}, intensity{INTENSITY}, direction{DIRECTION}, color{COLOR}, valid{1} {};
};

double ComputeLighting(
    Vector3D<double> Point,
    Vector3D<double> Normal,
    Vector3D<double> directiontoViewport,
    int specular,
    Light lightList[],
    int numberofLights,
    Object objectList[],
    int numberofObjects
);

#endif