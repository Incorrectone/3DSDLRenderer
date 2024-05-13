#include "include/shapes.h"

#include <vector>
#include <tuple>

shapes::SPHERE shapes::initSphere(std::vector<double> center, double radius, std::tuple<int, int, int> color){
    
    shapes::SPHERE sphereOBJ = {center, radius, color, 1};
    return sphereOBJ;

}
