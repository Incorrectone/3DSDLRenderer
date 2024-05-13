#include "include/constants.h"
#include "include/viewport.h"
#include "include/shapes.h"

#include <tuple>
#include <vector>
#include <limits>
#include <cmath>
#include <iostream>

std::vector<double> subtractVectors(std::vector<double> vector1, std::vector<double> vector2){
    std::vector<double> subtracted_vector;
    subtracted_vector.resize(0);

    for(int i = 0; i < vector1.size(); i++){
        subtracted_vector.push_back(vector1[i] - vector2[i]);
    }
    return subtracted_vector;
}

double vectorDotProduct(std::vector<double> vector1, std::vector<double> vector2){
    double dotProduct = 0;
    for(int i = 0; i < vector1.size(); i++){
        dotProduct += vector1[i] * vector2[i];
    }
    return dotProduct;
}

std::vector<double> viewport::CanvasToViewport(int canvasX, int canvasY){
    std::vector<double> viewportCoordinates;
    viewportCoordinates.resize(0);

    // Pg. 16
    viewportCoordinates.push_back(canvasX * constants::VEIWPORT_WIDTH / (double)constants::SCREEN_WIDTH);
    viewportCoordinates.push_back(canvasY * constants::VEIWPORT_HEIGHT / (double)constants::SCREEN_HEIGHT);
    viewportCoordinates.push_back(constants::VEIWPORT_DISTANCE);
    
    return viewportCoordinates;
}

std::tuple<double, double> viewport::IntersectRaySphere(std::vector<double> Camera, std::vector<double> viewportCoordinates, shapes::SPHERE sphere){
    
    double radius = sphere.radius;
    
    std::vector<double> CameraToSphere = subtractVectors(Camera, sphere.center);
    
    double a = vectorDotProduct(viewportCoordinates, viewportCoordinates);
    double b = vectorDotProduct(CameraToSphere, viewportCoordinates) * 2.0;
    double c = vectorDotProduct(CameraToSphere, CameraToSphere) - (radius * radius);

    double discriminant = b * b - 4 * a * c;

    if(discriminant < 0.0){
        return {std::numeric_limits<double>::max(), std::numeric_limits<double>::max()};
    }

    double t1 = ( - b + std::sqrt(discriminant) ) / (a * 2.0);
    double t2 = ( - b - std::sqrt(discriminant) ) / (a * 2.0);

    return {t1, t2};
}

std::tuple<int, int, int> viewport::TraceRay(std::vector<double> Camera, std::vector<double> viewportCoordinates, int t_min, int t_max, shapes::SPHERE objectList[], int listSize){
    
    double closest_intersection =  std::numeric_limits<double>::max();
    
    shapes::SPHERE closest_sphere;
    closest_sphere.valid = 0;

    for(int i = 0; i < listSize; i++){
        
        std::tuple<double, double> IntersectRay = viewport::IntersectRaySphere(Camera, viewportCoordinates, objectList[i]);
        
        double t1 = std::get<0>(IntersectRay);
        double t2 = std::get<1>(IntersectRay);

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
    
    return closest_sphere.color;
}
