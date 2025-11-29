#pragma once

#ifndef SKYBOX_H
#define SKYBOX_H

#include "vectors.h"
#include <string>

/*
    Initialize the skybox with a default color from constants::BACKGROUND_COLOR
*/
int initializeSkybox();

/*
    Initialize the skybox with an image from the given path
*/
int initializeSkybox(const char** imagePaths, const int count);

/*
    Frees Skybox image memory
*/
int freeSkybox();

/*
    Get the color from the skybox based on the ray direction
*/
Vector3D<int> getSkyboxColor(const Vector3D<double>& direction);

#endif