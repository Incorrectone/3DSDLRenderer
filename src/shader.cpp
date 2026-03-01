#include "vectors.h"
#include "objects.h"
#include "constants.h"

#include "shader.h"
#include "viewport.h"

#include <cmath>

double ComputeLighting(const Vector3D<double> &Point, const Vector3D<double> &Normal, const Vector3D<double> &directiontoViewport, const int specular){
    
    double intensity = 0.0;
    
    for(int i = 0; i < constants::numberofLights; i++){
        if(constants::lightList[i].type == 'a'){

            intensity += constants::lightList[i].intensity;

        } else {

            Vector3D<double> vectortoLight;

            if(constants::lightList[i].type == 'p'){
                //
                vectortoLight = constants::lightList[i].direction - Point;
            } else if(constants::lightList[i].type == 'd'){ 
                //
                vectortoLight = constants::lightList[i].direction;
            }

            // Shadows
            if(const returnType temp = ClosestIntersection(Point, vectortoLight, 0.0001, std::numeric_limits<double>::max()); temp.returnedObj.valid != -1)
                continue;
            // Diffuse

            if(const double dotproductNnL = vectortoLight.dot(Normal); dotproductNnL > 0){
                intensity += constants::lightList[i].intensity * dotproductNnL/(Normal.modulus() * vectortoLight.modulus());
            }

            //Specular

            if(specular != -1){

                Vector3D<double> reflectionofvectortoLight = ReflectedRay(Normal, vectortoLight);

                if(const double dotproductRnD = reflectionofvectortoLight.dot(directiontoViewport); dotproductRnD > 0){
                    intensity += constants::lightList[i].intensity * pow(dotproductRnD/(directiontoViewport.modulus() * reflectionofvectortoLight.modulus()), specular);
                    
                } 
            }
        }
    }
    
    return intensity;
}