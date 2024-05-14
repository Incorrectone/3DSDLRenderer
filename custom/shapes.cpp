#include "include/shapes.h"

#include "include/vectors.h"

shapes::SPHERE shapes::initSphere(VEC::VECTOR3D center, double radius, VEC::VECTOR3Di color){
    
    shapes::SPHERE sphereOBJ = {center, radius, color, 1};
    return sphereOBJ;

}
