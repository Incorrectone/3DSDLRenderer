#include "include/constants.h"
#include "include/vectormath.h"
#include "include/shapes.h"
#include "include/viewport.h"
#include "include/shader.h"

#include <limits>
#include <cmath>
#include <iostream>

VEC::VECTOR3D viewport::CanvasToViewport(int canvasX, int canvasY){
    VEC::VECTOR3D viewportCoordinates;

    // Pg. 16
    viewportCoordinates.x = canvasX * constants::VEIWPORT_WIDTH / (double)constants::SCREEN_WIDTH;
    viewportCoordinates.y = canvasY * constants::VEIWPORT_HEIGHT / (double)constants::SCREEN_HEIGHT;
    viewportCoordinates.z = constants::VEIWPORT_DISTANCE;
    
    return viewportCoordinates;
}

VEC::VECTOR2D viewport::IntersectRaySphere(VEC::VECTOR3D Camera, VEC::VECTOR3D viewportCoordinates, shapes::SPHERE sphere){
    
    double radius = sphere.radius;
    
    VEC::VECTOR3D CameraToSphere = vectormath::subtractVectors(Camera, sphere.center);
    
    double a = vectormath::vectorDotProduct(viewportCoordinates, viewportCoordinates);
    double b = vectormath::vectorDotProduct(CameraToSphere, viewportCoordinates) * 2.0;
    double c = vectormath::vectorDotProduct(CameraToSphere, CameraToSphere) - (radius * radius);

    double discriminant = b * b - 4 * a * c;

    if(discriminant < 0.0){
        return {std::numeric_limits<double>::max(), std::numeric_limits<double>::max()};
    }

    double t1 = ( - b + std::sqrt(discriminant) ) / (a * 2.0);
    double t2 = ( - b - std::sqrt(discriminant) ) / (a * 2.0);

    return {t1, t2};
}

VEC::VECTOR3Di viewport::TraceRay(VEC::VECTOR3D Camera, VEC::VECTOR3D viewportCoordinates, int t_min, int t_max, shapes::SPHERE objectList[], int objlistSize, shader::Light lightList[], int lightlistSize){
    
    double closest_intersection =  std::numeric_limits<double>::max();
    
    shapes::SPHERE closest_sphere;
    closest_sphere.valid = 0;

    for(int i = 0; i < objlistSize; i++){
        
        auto [t1, t2] = viewport::IntersectRaySphere(Camera, viewportCoordinates, objectList[i]);
        
        if( (t1 <= t_max && t1 >= t_min) && t1 < closest_intersection){
            closest_intersection = t1;
            closest_sphere = objectList[i];
        }
        if( (t2 <= t_max && t2 >= t_min) && t2 < closest_intersection){
            closest_intersection = t2;
            closest_sphere = objectList[i];
        }
    }

    if(closest_sphere.valid == 0){
        return constants::BACKGROUND_COLOR;
    }

    VEC::VECTOR3D pointofIntersection = vectormath::addVectors(Camera, vectormath::mscalarVector(closest_intersection, viewportCoordinates));
    VEC::VECTOR3D Normal = vectormath::subtractVectors(pointofIntersection, closest_sphere.center);
    Normal = vectormath::mscalarVector(1 / vectormath::absoluteValue(Normal), Normal);
     
    return vectormath::mscalarVector(shader::ComputeLighting(pointofIntersection, Normal, lightList, lightlistSize), closest_sphere.color);;
}
