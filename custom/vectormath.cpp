#include "include/vectormath.h"
#include "include/vectors.h"
#include "cmath"

VEC::VECTOR3D vectormath::colorFit(VEC::VECTOR3D color){
    VEC::VECTOR3D fittedcolorVec = color;
    
    if(fittedcolorVec.x > 255){
        fittedcolorVec.x = 255;
    }else if(fittedcolorVec.x < 0){
        fittedcolorVec.x = 0;
    }

    if(fittedcolorVec.y > 255){
        fittedcolorVec.y = 255;
    }else if(fittedcolorVec.y < 0){
        fittedcolorVec.y = 0;
    }

    if(fittedcolorVec.z > 255){
        fittedcolorVec.z = 255;
    }else if(fittedcolorVec.z < 0){
        fittedcolorVec.z = 0;
    }   

    return fittedcolorVec;
}

VEC::VECTOR3D vectormath::subtractVectors(VEC::VECTOR3D vector1, VEC::VECTOR3D vector2, int isColor){
    VEC::VECTOR3D subtracted_vector;

    subtracted_vector.x = vector1.x - vector2.x;
    subtracted_vector.y = vector1.y - vector2.y;
    subtracted_vector.z = vector1.z - vector2.z;

    if(isColor == 1){
        return vectormath::colorFit(subtracted_vector);
    }

    return subtracted_vector;
}

VEC::VECTOR3D vectormath::addVectors(VEC::VECTOR3D vector1, VEC::VECTOR3D vector2, int isColor){
    VEC::VECTOR3D added_vector;

    added_vector.x = vector1.x + vector2.x;
    added_vector.y = vector1.y + vector2.y;
    added_vector.z = vector1.z + vector2.z;

    if(isColor == 1){
        return vectormath::colorFit(added_vector);
    }

    return added_vector;
}

VEC::VECTOR3D vectormath::mscalarVector(double scalar, VEC::VECTOR3D vector, int isColor){
    VEC::VECTOR3D scaled_vector;

    scaled_vector.x = vector.x * scalar;
    scaled_vector.y = vector.y * scalar;
    scaled_vector.z = vector.z * scalar;

    if(isColor == 1){
        return vectormath::colorFit(scaled_vector);
    }

    return scaled_vector;
}

double vectormath::vectorDotProduct(VEC::VECTOR3D vector1, VEC::VECTOR3D vector2){
    return (vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z);
}

double vectormath::absoluteValue(VEC::VECTOR3D vector){
    return sqrt(vectormath::vectorDotProduct(vector, vector));
}

VEC::VECTOR3D vectormath::ReflectedRay(VEC::VECTOR3D Normal, VEC::VECTOR3D VectortobeReflected){
     return vectormath::subtractVectors(
        vectormath::mscalarVector(
            2.0,
            vectormath::mscalarVector(
                vectormath::vectorDotProduct(Normal, VectortobeReflected),
                Normal
            )
        ),
        VectortobeReflected
    );
}
