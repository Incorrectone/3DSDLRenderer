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
    viewportCoordinates.x = canvasX * constants::VEIWPORT_WIDTH / static_cast<double>(constants::SCREEN_WIDTH);
    viewportCoordinates.y = canvasY * constants::VEIWPORT_HEIGHT / static_cast<double>(constants::SCREEN_HEIGHT);
    viewportCoordinates.z = constants::VEIWPORT_DISTANCE;
    
    return viewportCoordinates;
}

Vector2D IntersectRaySphere(const Ray &ray_object, const Sphere &sphere){

    const double radius = sphere.radius;
    
    Vector3D<double> CameraToSphere = ray_object.origin - sphere.center;

    double b = CameraToSphere.dot(ray_object.direction);
    double c = CameraToSphere.dot(CameraToSphere) - (radius * radius);

    double discriminant = b * b - c;

    if(discriminant < 0.0){
        return {std::numeric_limits<double>::max(), std::numeric_limits<double>::max()};
    }

    double t1 = - b - std::sqrt(discriminant);
    double t2 = - b + std::sqrt(discriminant);

    return {t1, t2};
}

Vector2D IntersectRayPlane(const Ray &ray_object, const Plane &plane){
    
    double check = plane.normal.dot(-1 * ray_object.direction);

    if (check == 0.0){
        return {std::numeric_limits<double>::max(), std::numeric_limits<double>::max()};
    }

    double t1 = (plane.rh - plane.normal.dot(ray_object.origin)) * ( 1 / plane.normal.dot(ray_object.direction) );
    
    double t2 = t1;

    return {t1, t2};
}

Vector2D IntersectRay(const Ray &ray_object, Object object){
    if(object.type == 's')
        return IntersectRaySphere(ray_object, object.object.sphere);
    else if(object.type == 'p')
        return IntersectRayPlane(ray_object, object.object.plane);
}

returnType ClosestIntersection(const Ray &ray_object, const double t_min, const double t_max){
    
    double closest_intersection = t_max;
    Object * closest_object = nullptr;

    for(int i = 0; i < constants::numberofObjects; i++){
        // use intersectRay
        auto [t1, t2] = IntersectRay(ray_object, constants::objList[i]);
        
        if(t1 >= t_min && t1 < closest_intersection){
            closest_intersection = t1;
            closest_object = &constants::objList[i];
        }else if(t2 >= t_min && t2 < closest_intersection){
            closest_intersection = t2;
            closest_object = &constants::objList[i];
        }
    }

    return {closest_object, closest_intersection};
}

Vector3D<double> TraceRay(const Ray &ray_object, const double t_min, const double t_max, const int reflection_recursive){

    returnType temp = ClosestIntersection(ray_object, t_min, t_max);
    const Object * closest_object = temp.returnedObj;
    const double closest_intersection = temp.closest_intersection;

    if(closest_object == nullptr || closest_object->valid == -1){
        return getSkyboxColor(ray_object.direction);
    }

    Vector3D<double> Normal;

    Vector3D<double> pointofIntersection = ray_object.origin + closest_intersection * ray_object.direction;
    //get normal member func
    if(closest_object->type == 's'){
        Normal = pointofIntersection - closest_object->object.sphere.center;
        Normal = (1 / Normal.modulus()) * Normal;
    }else if(closest_object->type == 'p'){
        Normal = closest_object->object.plane.normal;
        Normal = (1 / Normal.modulus()) * Normal;
    }

    const Ray lighting_ray = {
        pointofIntersection,
        -1.0 * ray_object.direction
    };
    // get specular and get Color
    Vector3D<double> local_color = ComputeLighting(lighting_ray,
        Normal,
        closest_object->specular) * closest_object->color;

    // get roughness
    const double reflective = closest_object->reflective;
    if ((reflection_recursive <= 0) || (reflective <= 0)){
        return local_color.colorFit();
    }

    const Ray Reflected_ray = {
        pointofIntersection,
        ReflectedRay(Normal, -1.0 * ray_object.direction).normalize()
    };
    const Vector3D<double> reflective_color = TraceRay(Reflected_ray, 0.001, t_max, reflection_recursive - 1);

    return (((1 - reflective) * local_color) + (reflective * reflective_color)).colorFit();
}
