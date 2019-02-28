/*
FILE: regular.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019
*/

#include "codegen.h"
#include <random>

void _1d::Samples::Regular::Regular(std::vector<float>& values, size_t numValues, std::mt19937& rng)
{
    values.resize(numValues);
    for (size_t i = 0; i < numValues; ++i)
        values[i] = float(i) / float(numValues);
}

void _1d::Samples::Regular::RegularCentered(std::vector<float>& values, size_t numValues, std::mt19937& rng)
{
    values.resize(numValues);
    for (size_t i = 0; i < numValues; ++i)
        values[i] = float(i) / float(numValues - 1);
}

void _1d::Samples::Regular::RegularCenteredOffset(std::vector<float>& values, size_t numValues, std::mt19937& rng)
{
    float offset = 1.0f / float(numValues * 2);
    values.resize(numValues);
    for (size_t i = 0; i < numValues; ++i)
        values[i] = offset + float(i) / float(numValues);
}

void _1d::Samples::Regular::RegularJittered(std::vector<float>& values, size_t numValues, std::mt19937& rng)
{
    std::uniform_real_distribution<float> dist(0.0f, 1.0f / float(numValues));

    values.resize(numValues);
    for (size_t i = 0; i < numValues; ++i)
        values[i] = (float(i) / float(numValues)) + dist(rng);
}
