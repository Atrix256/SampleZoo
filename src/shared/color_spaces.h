/*
FILE: color_spaces.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/10/2019

Description:
Helper functions to convert between different color spaces
*/

#pragma once

#include <stdint.h>
#include <math.h>
#include <array>
#include "math.h"
#include "vector.h"

inline float LinearToSRGB(float value)
{
    return pow(value, 1.0f / 2.2f);
}

inline float SRGBToLinear(float value)
{
    return pow(value, 2.2f);
}

inline uint8_t FloatToU8(float value)
{
    return uint8_t(value * 255.0f + 0.5f);
}

// adapted from https://martin.ankerl.com/2009/12/09/how-to-create-random-colors-programmatically/
inline Vec3 HUEtoRGB(float H)
{
    float R = Clamp(abs(H * 6 - 3) - 1, 0.0f, 1.0f);
    float G = Clamp(2 - abs(H * 6 - 2), 0.0f, 1.0f);
    float B = Clamp(2 - abs(H * 6 - 4), 0.0f, 1.0f);
    return Vec3{ R, G, B };
}

inline Vec3 HSVToRGB(Vec3 HSV)
{
    Vec3 RGB = HUEtoRGB(HSV[0]);
    return ((RGB - 1.0f) * HSV[1] + 1.0f) * HSV[2];
}
