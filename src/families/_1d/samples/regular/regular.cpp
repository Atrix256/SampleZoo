/*
FILE: regular.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019
*/

#include "codegen.h"
#include <random>

void _1d::Samples::Regular::Regular(std::vector<float>& values, size_t numValues)
{
    values.resize(numValues);
    for (size_t i = 0; i < numValues; ++i)
        values[i] = float(i) / float(numValues);
}

void _1d::Samples::Regular::RegularCentered(std::vector<float>& values, size_t numValues)
{
    values.resize(numValues);
    for (size_t i = 0; i < numValues; ++i)
        values[i] = float(i) / float(numValues - 1);
}

void _1d::Samples::Regular::RegularCenteredOffset(std::vector<float>& values, size_t numValues)
{
    float offset = 1.0f / float(numValues * 2);
    values.resize(numValues);
    for (size_t i = 0; i < numValues; ++i)
        values[i] = offset + float(i) / float(numValues);
}

void _1d::Samples::Regular::RegularJittered(std::vector<float>& values, size_t numValues)
{
    // make sure we use "the good stuff". yes, it matters if the not good stuff gets in, it's a big difference.
    // https://blog.demofox.org/2017/03/15/neural-network-recipe-recognize-handwritten-digits-with-95-accuracy/
    static std::random_device rd("dev/random");
    static std::mt19937 rng(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f / float(numValues));

    values.resize(numValues);
    for (size_t i = 0; i < numValues; ++i)
        values[i] = (float(i) / float(numValues)) + dist(rng);
}
