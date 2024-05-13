#pragma once

#ifndef SHAPES_H
#define SHAPES_H

#include <vector>
#include <tuple>

namespace shapes{
    // A simple sphere
    typedef struct SPHERE_S {
        std::vector<double> center;
        double radius;
        std::tuple<int, int, int> color;
        int valid;
    } SPHERE;

    // Initilizes a sphere, with valid key = 1
    shapes::SPHERE initSphere(
        std::vector<double> center,
        double radius,
        std::tuple<int, int, int> color
    );
}

#endif
