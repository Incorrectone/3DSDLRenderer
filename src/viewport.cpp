#include "vectors.h"
#include "objects.h"
#include "constants.h"

#include "skybox.h"
#include "viewport.h"
#include "shader.h"

#include <limits>
#include <cmath>

Vector3D<double> ReflectedRay(const Vector3D<double> &Normal, const Vector3D<double> &raytobeReflected){
    return 2 * Normal * Normal.dot(raytobeReflected) - raytobeReflected;
}

Vector3D<double> CanvasToViewport(const int canvasX, const int canvasY){
    Vector3D<double> viewportCoordinates;

    // Pg. 16
    viewportCoordinates.x = canvasX * constants::VEIWPORT_WIDTH / (double)constants::SCREEN_WIDTH;
    viewportCoordinates.y = canvasY * constants::VEIWPORT_HEIGHT / (double)constants::SCREEN_HEIGHT;
    viewportCoordinates.z = constants::VEIWPORT_DISTANCE;
    
    return viewportCoordinates;
}

Vector2D IntersectRaySphere(const Vector3D<double> &Camera, const Vector3D<double> &viewportCoordinates, const Sphere &sphere){

    const double radius = sphere.radius;
    
    Vector3D<double> CameraToSphere = Camera - sphere.center;
    
    double a = viewportCoordinates.dot(viewportCoordinates);
    double b = CameraToSphere.dot(viewportCoordinates);
    double c = CameraToSphere.dot(CameraToSphere) - (radius * radius);

    double discriminant = b * b - a * c;

    if(discriminant < 0.0){
        return {std::numeric_limits<double>::max(), std::numeric_limits<double>::max()};
    }

    double t1 = ( - b - std::sqrt(discriminant) ) / (a);
    double t2 = ( - b + std::sqrt(discriminant) ) / (a);

    return {t1, t2};
}

Vector2D IntersectRayPlane(const Vector3D<double> &Camera, const Vector3D<double> &viewportCoordinates, const Plane &plane){
    
    double check = plane.normal.dot(-1 * viewportCoordinates);

    if (check == 0.0){
        return {std::numeric_limits<double>::max(), std::numeric_limits<double>::max()};
    }

    double t1 = (plane.rh - plane.normal.dot(Camera)) * ( 1 / plane.normal.dot(viewportCoordinates) );
    
    double t2 = t1;

    return {t1, t2};
}

Vector2D IntersectRay(const Vector3D<double> &Camera, const Vector3D<double> &viewportCoordinates, Object object){
    if(object.type == 's')
        return IntersectRaySphere(Camera, viewportCoordinates, object.object.sphere);
    else if(object.type == 'p')
        return IntersectRayPlane(Camera, viewportCoordinates, object.object.plane);
}

returnType ClosestIntersection(const Vector3D<double> &Camera, const Vector3D<double> &viewportCoordinates, const double t_min, const double t_max){
    
    double closest_intersection = t_max;
    Object closest_object;

    for(int i = 0; i < constants::numberofObjects; i++){
        auto [t1, t2] = IntersectRay(Camera, viewportCoordinates, constants::objList[i]);
        
        if(t1 >= t_min && t1 < closest_intersection){
            closest_intersection = t1;
            closest_object = constants::objList[i];
        }else if(t2 >= t_min && t2 < closest_intersection){
            closest_intersection = t2;
            closest_object = constants::objList[i];
        }
    }

    return {closest_object, closest_intersection};
}

Vector3D<double> TraceRay(const Vector3D<double> &Camera, const Vector3D<double> &viewportCoordinates, const double t_min, const double t_max, const int reflection_recursive){
    
    returnType temp = ClosestIntersection(Camera, viewportCoordinates, t_min, t_max);
    Object closest_object = temp.returnedObj;
    double closest_intersection = temp.closest_intersection;

    if(closest_object.valid == -1){
        return getSkyboxColor(viewportCoordinates);
    }

    Vector3D<double> Normal;

    Vector3D<double> pointofIntersection = Camera + closest_intersection * viewportCoordinates;
    if(closest_object.type == 's'){
        Normal = pointofIntersection - closest_object.object.sphere.center;
        Normal = (1 / Normal.modulus()) * Normal;
    }else if(closest_object.type == 'p'){
        Normal = closest_object.object.plane.normal;
        Normal = (1 / Normal.modulus()) * Normal;
    }
     
    Vector3D<double> local_color = ComputeLighting(pointofIntersection, Normal, -1.0 * viewportCoordinates, closest_object.specular) * closest_object.color;

    double reflective = closest_object.reflective;
    if ((reflection_recursive <= 0) || (reflective <= 0)){
        return local_color.colorFit();
    }

    Vector3D<double> Reflected_ray = ReflectedRay(Normal, -1.0 * viewportCoordinates);
    Vector3D<double> reflective_color = TraceRay(pointofIntersection, Reflected_ray, 0.001, t_max, reflection_recursive - 1);

    return (((1 - reflective) * local_color) + (reflective * reflective_color)).colorFit();
}
