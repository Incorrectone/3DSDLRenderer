//
// Created by incor on 3/4/26.
//

#pragma once

#ifndef RENDERER_OBJECTS_NEW_H
#define RENDERER_OBJECTS_NEW_H

#include "vectors.h"
#include "spectrum.h"
#include "materials.h"

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
    virtual ~Object() = default;

    virtual IntersectionReturn intersectRay(const Ray& ray) const = 0;
    virtual Vector3D<double> getNormal(const Vector3D<double> &Point) const = 0;
    virtual Vector3D<int> getColor(const Vector3D<double> &Point) const = 0;
    virtual double getRoughness(const Vector3D<double> &Point) const = 0;
    virtual double getSpecular(const Vector3D<double> &Point) const = 0;
};
// Sphere, Plane, Triangles, and custom objects

struct Sphere: public Object{
private:
    Vector3D<int> base_color;
    double base_specular;
    double base_roughness;

    bool is_visible;
public:

};

#endif //RENDERER_OBJECTS_NEW_H
