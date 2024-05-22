#pragma once

#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "vectors.h"
#include "shapes.h"
#include "shader.h"

namespace viewport{

    Vector3D<double> ReflectedRay(Vector3D<double> Normal, Vector3D<double> raytobeReflected);
    
    /*
        Since Viewport is a screen in 3D
        We nee to convert Canvas Coordinates <2D> in Veiwport Coords <3D>
    */
    Vector3D<double> CanvasToViewport(int canvasX, int canvasY);

    /*
        Checks whether a ray intersects a sphere, with respect to Camera and viewport coordinates
    */
    Vector2D IntersectRaySphere(
        Vector3D<double> Camera, 
        Vector3D<double> viewportCoordinates, 
        Sphere sphere
        );
    
    Vector2D IntersectRayPlane(
        Vector3D<double> Camera, 
        Vector3D<double> viewportCoordinates, 
        Plane plane
        );
    
    Vector2D IntersectRay(
        Vector3D<double> Camera, 
        Vector3D<double> viewportCoordinates, 
        Object object
        );
    
    returnType ClosestIntersection(
        Vector3D<double> Camera, 
        Vector3D<double> viewportCoordinates, 
        double t_min, 
        double t_max,  
        Object objectList[],
        int objlistSize
    );

    /*
        Traces a ray from Camera to an object from the object list
        Object list currently uses Spheres but will Change
    */
   Vector3D<double> TraceRay(
        Vector3D<double> Camera, 
        Vector3D<double> viewportCoordinates, 
        double t_min, 
        double t_max,  
        Object objectList[],
        int objlistSize,
        Light lightList[],
        int lightlistSize,
        int reflection_recursive
        );
}

#endif