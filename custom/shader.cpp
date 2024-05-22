#include "include/vectors.h"
#include "include/shader.h"
#include "include/viewport.h"

#include <cmath>

double ComputeLighting(Vector3D<double> Point, Vector3D<double> Normal, Vector3D<double> directiontoViewport, int specular, Light lightList[], int numberofLights, Object objectList[], int numberofObjects){
    
    double intensity = 0.0;
    
    for(int i = 0; i < numberofLights; i++){
        if(lightList[i].type == 'a'){

            intensity += lightList[i].intensity;

        } else {

            Vector3D<double> vectortoLight;

            if(lightList[i].type == 'p'){
                //
                vectortoLight = lightList[i].direction - Point;
            } else if(lightList[i].type == 'a'){ 
                //
                vectortoLight = lightList[i].direction;
            }

            // Shadows
            returnType temp = viewport::ClosestIntersection(Point, vectortoLight, 0.0001, std::numeric_limits<double>::max(), objectList, numberofObjects);
            if(temp.returnedObj.valid != -1)
                continue;
            // Diffuse

            double dotproductNnL = vectortoLight.dot(Normal);
            if(dotproductNnL > 0){
                intensity += lightList[i].intensity * dotproductNnL/(Normal.modulus() * vectortoLight.modulus());
            }

            //Specular

            if(specular != -1){

                Vector3D<double> reflectionofvectortoLight = viewport::ReflectedRay(Normal, vectortoLight);
              
                double dotproductRnD = reflectionofvectortoLight.dot(directiontoViewport);
                if(dotproductRnD > 0){
                    intensity += lightList[i].intensity * pow(dotproductRnD/(directiontoViewport.modulus() * reflectionofvectortoLight.modulus()), specular);
                    
                } 
            }
        }
    }
    
    return intensity;
}