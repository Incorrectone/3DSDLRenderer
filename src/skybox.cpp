#include "constants.h"
#include "vectors.h"
#include "skybox.h"

#include <string>
#include <array>
#include <cmath>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static const int numberOfFaces = 6;
/*
    1. Right (+X)
    2. Left (−X)
    3. Top (+Y)
    4. Bottom (−Y)
    5. Front (+Z)
    6. Back (−Z)
*/
static std::array<std::string, numberOfFaces> skyboxFaces = {"", "", "", "", "", ""};
static bool isSkyboxInitialized = false;

static int width[numberOfFaces] = {0, 0, 0, 0, 0, 0};
static int height[numberOfFaces] = {0, 0, 0, 0, 0, 0};
static int channels[numberOfFaces] = {0, 0, 0, 0, 0, 0};
static unsigned char* data[numberOfFaces] = {NULL, NULL, NULL, NULL, NULL, NULL};

int initializeSkybox() {
    skyboxFaces.fill("");
    isSkyboxInitialized = true;

    return 0;
}

int initializeSkybox(const char** imagePaths, const int count) {
    if (isSkyboxInitialized) {
        freeSkybox(); 
    }

    if (count != numberOfFaces){
        std::cout << "The count attr must match the number of faces of a cube (6)." << std::endl;
        return -1;
    }

    for(int i = 0; i < numberOfFaces; i++){
        skyboxFaces[i] = imagePaths[i];
        data[i] = stbi_load(skyboxFaces[i].c_str(), &width[i], &height[i], &channels[i], 3);
        if( data[i] == NULL){
            std::cout << "Error loading Skybox Image file {" << i << "}" << std::endl;
            for(int j = 0; j < i; j++){
                if(data[j]){
                    stbi_image_free(data[j]);
                    data[j] = NULL;
                }
            }
            return -1;
        }
    }

    isSkyboxInitialized = true;
    return 0;
}

int freeSkybox() {
    for (int i = 0; i < numberOfFaces; i++) {
        if (data[i] != nullptr) {
            stbi_image_free(data[i]);
            data[i] = nullptr;
        }
    }
    isSkyboxInitialized = false;
    return 0;
}

Vector3D<int> getSkyboxColor(const Vector3D<double>& direction){
    if(!isSkyboxInitialized){
        return constants::BACKGROUND_COLOR;
    }

    // https://en.wikipedia.org/wiki/Cube_mapping
    
    double x = direction.x;
    double y = direction.y;
    double z = direction.z;
    
    double absX = std::abs(x);
    double absY = std::abs(y);
    double absZ = std::abs(z);

    int faceIndex = 0;
    double u = 0.0;
    double v = 0.0;
    double maxAxis = 0.0;

    if (absX >= absY && absX >= absZ) {
        maxAxis = absX;
        if (x > 0) {
            faceIndex = 0; // Right
            u = -z; 
            v = -y;
        } else {
            faceIndex = 1; // Left
            u = z; 
            v = -y;
        }
    } else if (absY >= absX && absY >= absZ) {
        maxAxis = absY;
        if (y > 0) {
            faceIndex = 2; // Top
            u = x; 
            v = z;
        } else {
            faceIndex = 3; // Bottom
            u = x; 
            v = -z;
        }
    } else {
        maxAxis = absZ;
        if (z > 0) {
            faceIndex = 4; // Front
            u = x; 
            v = -y;
        } else {
            faceIndex = 5; // Back
            u = -x; 
            v = -y;
        }
    }

    // see if image is present or not
    if (data[faceIndex] == nullptr) {
        return constants::BACKGROUND_COLOR;
    }

    double uc = 0.5 * ( u / maxAxis + 1.0 );
    double vc = 0.5 * ( v / maxAxis + 1.0 );

    int imgWidth = width[faceIndex];
    int imgHeight = height[faceIndex];
    int imgChannels = channels[faceIndex];

    int px = static_cast<int>(uc * imgWidth);
    int py = static_cast<int>(vc * imgHeight);
    
    px = std::max(0, std::min(px, imgWidth - 1));
    py = std::max(0, std::min(py, imgHeight - 1));

    int pixelIndex = (py * imgWidth + px) * imgChannels;

    unsigned char r = data[faceIndex][pixelIndex];
    unsigned char g = data[faceIndex][pixelIndex + 1];
    unsigned char b = data[faceIndex][pixelIndex + 2];

    return Vector3D<int>(static_cast<int>(r), static_cast<int>(g), static_cast<int>(b));
}



