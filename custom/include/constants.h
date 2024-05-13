#pragma once

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include <tuple>

namespace constants
{
	const std::vector<int> ORIGIN({0 ,0 ,0});
    const std::tuple<int, int, int> BACKGROUND_COLOR = std::make_tuple(255, 255, 255);

    constexpr int VEIWPORT_WIDTH { 1 };
    constexpr int VEIWPORT_HEIGHT { 1 };
    constexpr int VEIWPORT_DISTANCE { 1 };
    constexpr int FIELDOFVIEW { 53 }; // in Degrees


    constexpr int SCREEN_WIDTH { 600 };
    constexpr int SCREEN_HEIGHT { 600 };

}
#endif