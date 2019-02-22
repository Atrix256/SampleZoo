/*
FILE: irrational_numbers.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019
*/

#include "codegen.h"

static const float c_goldenRatioConjugate = 0.61803398875f;
static const float c_pi = 3.14159265359f;

void Samples::_1d::IrrationalNumbers::GoldenRatioZero(std::vector<float>& values, size_t numValues)
{
    values.resize(numValues);
    for (size_t i = 0; i < numValues; ++i)
        values[i] = std::fmodf(float(i) * c_goldenRatioConjugate, 1.0f);
}

void Samples::_1d::IrrationalNumbers::GoldenRatio(std::vector<float>& values, size_t numValues)
{
    values.resize(numValues);
    for (size_t i = 0; i < numValues; ++i)
        values[i] = std::fmodf(float(i + 1) * c_goldenRatioConjugate, 1.0f); // Don't sample at zero, as first sample!
}

void Samples::_1d::IrrationalNumbers::Pi(std::vector<float>& values, size_t numValues)
{
    // the part to the left of the decimal point doesn't matter for this, and just makes us hit precision problems sooner.
    float piMod1 = std::fmodf(c_pi, 1.0f);

    values.resize(numValues);
    for (size_t i = 0; i < numValues; ++i)
        values[i] = std::fmodf(float(i + 1) * piMod1, 1.0f); // Don't sample at zero, as first sample!
}

void Samples::_1d::IrrationalNumbers::Sqrt2(std::vector<float>& values, size_t numValues)
{
    // the part to the left of the decimal point doesn't matter for this, and just makes us hit precision problems sooner.
    float sqrt2Mod1 = std::fmodf(std::sqrtf(2.0f), 1.0f);

    values.resize(numValues);
    for (size_t i = 0; i < numValues; ++i)
        values[i] = std::fmodf(float(i + 1) * sqrt2Mod1, 1.0f); // Don't sample at zero, as first sample!
}
