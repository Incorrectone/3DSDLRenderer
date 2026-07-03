//
// Created by incor on 3/4/26.
//

#pragma once

#ifndef LIGHTS_H
#define LIGHTS_H

// Have to change this too, to use virtual functions
struct Light{
    char type;
    double intensity;
    double phase;
    double wavelength;
    Vector3D<double> direction;
    Vector3D<int> color;
    int valid;

    Light () {};
    Light(const char TYPE, const double INTENSITY , const Vector3D<double> &DIRECTION, const Vector3D<double> &COLOR) :
    type{TYPE}, intensity{INTENSITY}, direction{DIRECTION}, color{COLOR}, valid{1} {};
};

inline Object::Object(const Vector3D<int> c, const double spec, const double rough, const bool visib): base_color(c), base_specular(spec), base_roughness(rough), is_visible(visib){}


#endif