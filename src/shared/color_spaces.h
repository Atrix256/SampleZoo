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

inline float LinearToSRGB(float value)
{
    return pow(value, 1.0f / 2.2f);
}

inline float SRGBToLinear(float value)
{
    return pow(value, 2.2f);
}
