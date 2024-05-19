#include "include/vectormath.h"
#include "include/vectors.h"
#include "cmath"

VEC::VECTOR3D vectormath::subtractVectors(VEC::VECTOR3D vector1, VEC::VECTOR3D vector2){
    VEC::VECTOR3D subtracted_vector;

    subtracted_vector.x = vector1.x - vector2.x;
    subtracted_vector.y = vector1.y - vector2.y;
    subtracted_vector.z = vector1.z - vector2.z;

    return subtracted_vector;
}

VEC::VECTOR3D vectormath::addVectors(VEC::VECTOR3D vector1, VEC::VECTOR3D vector2){
    VEC::VECTOR3D added_vector;

    added_vector.x = vector1.x + vector2.x;
    added_vector.y = vector1.y + vector2.y;
    added_vector.z = vector1.z + vector2.z;

    return added_vector;
}

VEC::VECTOR3Di vectormath::addVectors(VEC::VECTOR3Di vector1, VEC::VECTOR3Di vector2, int isColor){
    VEC::VECTOR3Di added_vector;

    added_vector.x = vector1.x + vector2.x;
    added_vector.y = vector1.y + vector2.y;
    added_vector.z = vector1.z + vector2.z;
    // if(isColor == 1){
    //     if(added_vector.x > 255){
    //         added_vector.x = 255;
    //     }else if(added_vector.x < 0){
    //         added_vector.x = 0;
    //     }
    //     if(added_vector.y > 255){
    //         added_vector.y = 255;
    //     }else if(added_vector.y < 0){
    //         added_vector.y = 0;
    //     }
    //     if(added_vector.z > 255){
    //         added_vector.z = 255;
    //     }else if(added_vector.z < 0){
    //         added_vector.z = 0;
    //     }        
    // }

    return added_vector;
}


double vectormath::vectorDotProduct(VEC::VECTOR3D vector1, VEC::VECTOR3D vector2){
    return (vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z);
}

double vectormath::absoluteValue(VEC::VECTOR3D vector){
    return sqrt(vectormath::vectorDotProduct(vector, vector));
}

VEC::VECTOR3D vectormath::mscalarVector(double scalar, VEC::VECTOR3D vector){
    VEC::VECTOR3D scaled_vector;

    scaled_vector.x = vector.x * scalar;
    scaled_vector.y = vector.y * scalar;
    scaled_vector.z = vector.z * scalar;

    return scaled_vector;
}

VEC::VECTOR3Di vectormath::mscalarVector(double scalar, VEC::VECTOR3Di vector, int isColor){
    VEC::VECTOR3Di scaled_vector;

    scaled_vector.x = vector.x * scalar;
    scaled_vector.y = vector.y * scalar;
    scaled_vector.z = vector.z * scalar;
    if(isColor == 1){
        if(scaled_vector.x > 255){
            scaled_vector.x = 255;
        }else if(scaled_vector.x < 0){
            scaled_vector.x = 0;
        }
        if(scaled_vector.y > 255){
            scaled_vector.y = 255;
        }else if(scaled_vector.y < 0){
            scaled_vector.y = 0;
        }
        if(scaled_vector.z > 255){
            scaled_vector.z = 255;
        }else if(scaled_vector.z < 0){
            scaled_vector.z = 0;
        }        
    }

    return scaled_vector;
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
