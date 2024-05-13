#pragma once

#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "shapes.h"

#include <vector>
#include <tuple>

namespace viewport{
    
    /*
        Since Viewport is a screen in 3D
        We nee to convert Canvas Coordinates <2D> in Veiwport Coords <3D>
    */
    std::vector<double> CanvasToViewport(int canvasX, int canvasY);

    /*
        Checks whether a ray intersects a sphere, with respect to Camera and viewport coordinates
    */
    std::tuple<double, double> IntersectRaySphere(
        std::vector<double> Camera, 
        std::vector<double> viewportCoordinates, 
        shapes::SPHERE sphere
        );

    /*
        Traces a ray from Camera to an object from the object list
        Object list currently uses Spheres but will Change
    */
    std::tuple<int, int, int> TraceRay(
        std::vector<double> Camera, 
        std::vector<double> viewportCoordinates, 
        int t_min, 
        int t_max,  
        shapes::SPHERE objectList[],
        int listSize
        );
}

#endif