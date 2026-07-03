//
// Created by incor on 2/7/26.
//

#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include "spectrum.h"

struct Material {

};

struct SpectralMaterial : public Material {
private:
	Spectrum base_color;
};

#endif