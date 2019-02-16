/*
FILE: math.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/10/2019
*/

# pragma once

#include <algorithm>

inline float SmoothStep(float value, float min, float max)
{
    float x = (value - min) / (max - min);
    x = std::min(x, 1.0f);
    x = std::max(x, 0.0f);

    return 3.0f * x * x - 2.0f * x * x * x;
}

template <typename T>
T Lerp(T A, T B, float t)
{
    return T(float(A) * (1.0f - t) + float(B) * t);
}

template <typename T>
T Clamp(T Value, T Min, T Max)
{
    if (Value <= Min)
        return Min;
    else if (Value >= Max)
        return Max;
    else
        return Value;
}