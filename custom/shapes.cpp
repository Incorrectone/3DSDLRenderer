#include "include/shapes.h"

#include "include/vectors.h"

shapes::SPHERE shapes::initSphere(VEC::VECTOR3D center, double radius, VEC::VECTOR3Di color, int specular, double reflective){
    
    shapes::SPHERE sphereOBJ = {center, radius, color, specular, reflective, 's', 1};
    return sphereOBJ;

}

shapes::PLANE shapes::initPlane(VEC::VECTOR3D Normal, double d, VEC::VECTOR3Di color, int specular,  double reflective){
    shapes::PLANE planeOBJ = {Normal, d, color, specular, reflective, 'p', 1};
    return planeOBJ;
}
