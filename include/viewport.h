#pragma once

#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "vectors.h"
#include "objects.h"

Vector3D<double> ReflectedRay(const Vector3D<double> &Normal, const Vector3D<double> &raytobeReflected);

/*
    Since Viewport is a screen in 3D
    We nee to convert Canvas Coordinates <2D> in Veiwport Coords <3D>
*/
Vector3D<double> CanvasToViewport(int canvasX, int canvasY);

/*
    Checks whether a ray intersects a sphere, with respect to Camera and viewport coordinates
*/
Vector2D IntersectRaySphere(
    const Ray &ray_object,
    const Sphere &sphere
    );

/*
    Checks whether a ray intersects a plane, with respect to Camera and viewport coordinates
*/
Vector2D IntersectRayPlane(
    const Ray &ray_object,
    const Plane &plane
    );

/*
    Applys the correct intersection function based on object type
*/
Vector2D IntersectRay(
    const Ray &ray_object,
    Object object
    );

/*
    Finds the closest intersection the Camera to an object from the object list
*/
returnType ClosestIntersection(
    const Ray &ray_object,
    double t_min,
    double t_max
);

/*
    Traces a ray from Camera to an object from the object list
    Object list currently uses Spheres but will Change
*/
Vector3D<double> TraceRay(
    const Ray &ray_object,
    double t_min, 
    double t_max,  
    int reflection_recursive
    );

#endif