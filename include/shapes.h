#pragma once

#ifndef SHAPES_H
#define SHAPES_H

#include "vectors.h"
#include <iostream>

struct type_ID{ 
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
    
    Sphere(Vector3D<double> CENTER = Vector3D<double>({0, 0, 0}), double RADIUS = 1) : center{CENTER}, radius{RADIUS} {} 
};

struct Plane{
    Vector3D<double> normal;
    double rh;

    Plane(Vector3D<double> NORMAL = Vector3D<double>({0, 0, 0}), double RIGHT = 0) : normal{NORMAL}, rh{RIGHT} {} 
};

struct Triangle{
    Vector3D<double> normal;
    double rh;
    Vector3D<double> p1;
    Vector3D<double> p2;
    Vector3D<double> p3;

    Triangle(Vector3D<double> NORMAL = Vector3D<double>({0, 0, 0}), double RIGHT = 1, Vector3D<double> P1 = Vector3D<double>({0, 0, 0}), Vector3D<double> P2 = Vector3D<double>({0, 1, 0}), Vector3D<double> P3 = Vector3D<double>({0, 0, 1})) : normal{NORMAL}, rh{RIGHT}, p1{P1}, p2{P2}, p3{P3} {}
};

union universalObj{
    Plane plane;
    Sphere sphere;
    Triangle triangle;
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
    
    Object(char t) : Shape() {
        type = t;
        valid = 1;
        
        if(type == 'p')
            object.plane;
        if(type == 's')
            object.sphere;
    }

    Object(Vector3D<double> vec, double r, Vector3D<double> P1, Vector3D<double> P2, Vector3D<double> P3, Vector3D<int> COLOR = Vector3D<int>({126, 126, 126}), int SPECULAR = -1, double REFLECTION = -1) {
        type = 't';
        valid = 1;
        color = COLOR;
        specular = SPECULAR;
        reflective = REFLECTION;
        object.triangle = {vec, r, P1, P2, P3};
    }
};

struct returnType{
        Object returnedObj;
        double closest_intersection;
};

#endif
