#pragma once

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "vectors.h"
#include "objects.h"

namespace constants
{
	const Vector3D ORIGIN {0 ,0 ,0};
    const Vector3D BACKGROUND_COLOR {0, 0, 0};

    const int RECURSION_DEPTH { 3 };

    constexpr double VEIWPORT_WIDTH { 1 };
    constexpr double VEIWPORT_HEIGHT { 1 };
    constexpr double VEIWPORT_DISTANCE { 1 };
    constexpr int FIELDOFVIEW { 53 }; // in Degrees

    constexpr int SCREEN_WIDTH { 800 };
    constexpr int SCREEN_HEIGHT { 800 };

    const int numberofObjects = 4;
	extern Object objList[numberofObjects];
    
	const int numberofLights = 3;
	extern Light lightList[numberofLights];
}
#endif
