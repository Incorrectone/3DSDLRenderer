#pragma once

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "vectors.h"

namespace constants
{
	const Vector3D ORIGIN {0 ,0 ,0};
    const Vector3D BACKGROUND_COLOR {135, 206, 235};

    const int RECURSION_DEPTH { 3 };

    constexpr double VEIWPORT_WIDTH { 1 };
    constexpr double VEIWPORT_HEIGHT { 1 };
    constexpr double VEIWPORT_DISTANCE { 1 };
    constexpr int FIELDOFVIEW { 53 }; // in Degrees


    constexpr int SCREEN_WIDTH { 1600 };
    constexpr int SCREEN_HEIGHT { 1600 };

}
#endif
