//
// Created by incor on 3/4/26.
//

#pragma once

#ifndef RENDERER_OBJECTS_NEW_H
#define RENDERER_OBJECTS_NEW_H

#include "vectors.h"

struct Object;

struct Ray {
    Vector3D<double> origin;
    Vector3D<double> direction;
};

struct IntersectionReturn {
    bool hit;
    double distance;
    const Object * hit_object_ptr;
};

struct Object {
    Vector3D<int> base_color;
    double base_specular;
    double base_roughness;

    bool is_visible;

    Object(Vector3D<int> c, int spec, double rough, bool visib);

    virtual ~Object() = default;

    virtual IntersectionReturn intersectRay(const Ray& ray) const = 0;
    virtual Vector3D<double> getNormal(const Vector3D<double> &Point) const = 0;
    virtual Vector3D<int> getColor(const Vector3D<double> &Point) const = 0;
    virtual double getRoughness(const Vector3D<double> &Point) const = 0;
    virtual double getSpecular(const Vector3D<double> &Point) const = 0;
};

// Sphere, Plane, Triangles, and custom objects


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

#endif //RENDERER_OBJECTS_NEW_H
