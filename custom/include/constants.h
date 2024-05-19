#pragma once

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "vectors.h"

namespace constants
{
	const VEC::VECTOR3D ORIGIN({0 ,0 ,0});
    const VEC::VECTOR3Di BACKGROUND_COLOR({0, 0, 0});

    const int RECURSION_DEPTH { 3 };

    constexpr double VEIWPORT_WIDTH { 1 };
    constexpr double VEIWPORT_HEIGHT { 1 };
    constexpr double VEIWPORT_DISTANCE { 1 };
    constexpr int FIELDOFVIEW { 53 }; // in Degrees


    constexpr int SCREEN_WIDTH { 600 };
    constexpr int SCREEN_HEIGHT { 600 };

}
#endif