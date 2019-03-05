/*
FILE: irrational_numbers.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 3/4/2019
*/

#include "codegen.h"

static const float c_goldenRatioConjugate = 0.61803398875f;
static const float c_pi = 3.14159265359f;

void _2d::Samples::IrrationalNumbers::R2(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    // Generalized golden ratio to 2d.
    // Solution to x^3 = x + 1
    // AKA plastic constant.
    // from http://extremelearning.com.au/unreasonable-effectiveness-of-quasirandom-sequences/
    float g = 1.32471795724474602596f;
    float a1 = 1.0f / g;
    float a2 = 1.0f / (g*g);

    values.resize(numValues);
    for (int i = 0; i < numValues; ++i)
    {
        values[i][0] = fmodf(0.5f + a1 * float(i), 1.0f);
        values[i][1] = fmodf(0.5f + a2 * float(i), 1.0f);
    }
}

void _2d::Samples::IrrationalNumbers::R2Jittered(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    // A jitter is added to R2 to give it blue noise like properties.
    // from http://extremelearning.com.au/a-simple-method-to-construct-isotropic-quasirandom-blue-noise-point-sequences/
    float g = 1.32471795724474602596f;
    float a1 = 1.0f / g;
    float a2 = 1.0f / (g*g);

    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    static const float c_magicNumber = 0.732f;

    values.resize(numValues);
    for (int i = 0; i < numValues; ++i)
    {
        values[i][0] = fmodf(dist(rng) * c_magicNumber / sqrtf(float(i + 1)) + a1 * float(i), 1.0f);
        values[i][1] = fmodf(dist(rng) * c_magicNumber / sqrtf(float(i + 1)) + a2 * float(i), 1.0f);
    }
}
