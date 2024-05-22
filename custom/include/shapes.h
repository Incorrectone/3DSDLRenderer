#pragma once

#ifndef SHAPES_H
#define SHAPES_H

#include "vectors.h"
#include <iostream>

struct type_ID{ // level 1 class
    int uniqueID; // Unique ID Dunno how to implement
    char type; // Type for primitive shapes 
    int valid;

    type_ID(char TYPE = 'u', int ID = -1) : uniqueID{ID}, type{TYPE}, valid{-1} {}
};

struct Shape{ // level 2 class 
    Vector3D<int> color;
    int specular;
    double reflective;

    Shape(Vector3D<int> COLOR = Vector3D<int>({126, 126, 126}), int SPECULAR = -1, double REFLECTION = -1) : color{COLOR}, specular{SPECULAR}, reflective{REFLECTION} {} // General Access Constructor
};

struct Sphere{
    Vector3D<double> center;
    double radius;
    
    Sphere(Vector3D<double> CENTER, double RADIUS) : center{CENTER}, radius{RADIUS} {} 
    Sphere() : center{0, 0, 0}, radius{1} {}
};

struct Plane{
    Vector3D<double> normal;
    double rh;

    Plane(Vector3D<double> NORMAL, double RIGHT) : normal{NORMAL}, rh{RIGHT} {} 
    Plane() : normal{0, 0, 0}, rh{1} {}
};


union universalObj{
    Plane plane;
    Sphere sphere;
    universalObj () {}
};

struct Object : type_ID, Shape{
    universalObj object;

    Object() : type_ID() {}

    Object(Vector3D<double> vec, double r, char t, Vector3D<int> COLOR = Vector3D<int>({126, 126, 126}), int SPECULAR = -1, double REFLECTION = -1) {
        type = t;
        valid = 1;
        color = COLOR;
        specular = SPECULAR;
        reflective = REFLECTION;
        
        if(type == 'p')
            object.plane = {vec, r};
        if(type == 's')
            object.sphere = {vec, r};
    }
};

struct returnType{
        Object returnedObj;
        double closest_intersection;
};

#endif
