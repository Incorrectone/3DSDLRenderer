#include "include/vectors.h"
#include "include/shader.h"
#include "include/vectormath.h"

#include <cmath>

shader::Light shader::initLight(char type, double intensity,VEC::VECTOR3D direction, VEC::VECTOR3Di color){
    shader::Light lightOBJ = {type, intensity, direction, color, 1};
    return lightOBJ;
}

double shader::ComputeLighting(VEC::VECTOR3D Point, VEC::VECTOR3D Normal, VEC::VECTOR3D directiontoViewport, int specular, Light lightList[], int numberofLights){
    double intensity = 0.0;
    for(int i = 0; i < numberofLights; i++){
        if(lightList[i].type == 'a'){
            intensity += lightList[i].intensity;
        } else {

            VEC::VECTOR3D vectortoLight({0, 0, 0});
            if(lightList[i].type == 'p'){
                vectortoLight = vectormath::subtractVectors(lightList[i].direction, Point);
            } else if(lightList[i].type == 'a'){
                vectortoLight = lightList[i].direction;
            }

            // Diffuse

            double dotproductNnL = vectormath::vectorDotProduct(vectortoLight, Normal);
            if(dotproductNnL > 0){
                intensity += lightList[i].intensity * dotproductNnL/(vectormath::absoluteValue(Normal) * vectormath::absoluteValue(vectortoLight));
            }

            //Specular

            if(specular != -1){

                VEC::VECTOR3D reflectionofvectortoLight = vectormath::subtractVectors(
                    vectormath::mscalarVector(
                        2.0,
                        vectormath::mscalarVector(
                            vectormath::vectorDotProduct(Normal, vectortoLight),
                            Normal
                        )
                    ),
                    vectortoLight
                );

                double dotproductRnD = vectormath::vectorDotProduct(reflectionofvectortoLight, directiontoViewport);
                if(dotproductRnD > 0){
                    intensity += lightList[i].intensity * pow(dotproductRnD/(vectormath::absoluteValue(directiontoViewport) * vectormath::absoluteValue(reflectionofvectortoLight)), specular);
                    
                } 
            }
        }
    }
    
    return intensity;
}