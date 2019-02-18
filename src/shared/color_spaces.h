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
inline std::array<float, 3> HSVToRGB(float hue, float saturation, float value)
{
    float r, g, b;

    int h_i = int(hue * 6.0f);
    float f = hue * 6.0f - h_i;
    float p = value * (1.0f - saturation);
    float q = value * (1.0f - f * saturation);
    float t = value * (1.0f - (1.0f - f) * saturation);
    switch (h_i)
    {
        case 0:
        {
            r = value;
            g = t;
            b = p;
            break;
        }
        case 1:
        {
            r = q;
            g = value;
            b = p;
            break;
        }
        case 2:
        {
            r = p;
            g = value;
            b = t;
            break;
        }
        case 3:
        {
            r = p;
            g = q;
            b = value;
            break;
        }
        case 4:
        {
            r = t;
            g = p;
            b = value;
            break;
        }
        case 5:
        {
            r = value;
            g = p;
            b = q;
            break;
        }
    }
    return { r, g, b };
}
