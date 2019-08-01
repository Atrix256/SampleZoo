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

// t is a value that goes from 0 to 1 to interpolate in a C1 continuous way across uniformly sampled data points.
// when t is 0, this will return B.  When t is 1, this will return C.  Inbetween values will return an interpolation
// between B and C.  A and D are used to calculate slopes at the edges.
template <typename T>
T CubicHermite (T A, T B, T C, T D, float t)
{
    T a = -A / 2.0f + (3.0f*B) / 2.0f - (3.0f*C) / 2.0f + D / 2.0f;
    T b = A - (5.0f*B) / 2.0f + 2.0f*C - D / 2.0f;
    T c = -A / 2.0f + C / 2.0f;
    T d = B;

    return a*t*t*t + b*t*t + c*t + d;
}
