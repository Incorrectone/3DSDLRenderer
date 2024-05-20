#pragma once

#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "shapes.h"
#include "shader.h"

#include "vectors.h"

namespace viewport{
    
    /*
        Since Viewport is a screen in 3D
        We nee to convert Canvas Coordinates <2D> in Veiwport Coords <3D>
    */
    VEC::VECTOR3D CanvasToViewport(int canvasX, int canvasY);

    /*
        Checks whether a ray intersects a sphere, with respect to Camera and viewport coordinates
    */
    VEC::VECTOR2D IntersectRaySphere(
        VEC::VECTOR3D Camera, 
        VEC::VECTOR3D viewportCoordinates, 
        shapes::SPHERE sphere
        );
    
    shapes::returnType ClosestIntersection(
        VEC::VECTOR3D Camera, 
        VEC::VECTOR3D viewportCoordinates, 
        double t_min, 
        double t_max,  
        shapes::SPHERE objectList[],
        int objlistSize
    );

    /*
        Traces a ray from Camera to an object from the object list
        Object list currently uses Spheres but will Change
    */
   VEC::VECTOR3D TraceRay(
        VEC::VECTOR3D Camera, 
        VEC::VECTOR3D viewportCoordinates, 
        double t_min, 
        double t_max,  
        shapes::SPHERE objectList[],
        int objlistSize,
        shader::Light lightList[],
        int lightlistSize,
        int reflection_recursive
        );
}

#endif