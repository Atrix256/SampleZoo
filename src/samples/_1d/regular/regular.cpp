/*
FILE: regular.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019
*/

#include "codegen.h"

void Samples::_1d::Regular::Regular(std::vector<float>& values, size_t numValues)
{
    values.resize(numValues);
    for (size_t i = 0; i < numValues; ++i)
        values[i] = float(i) / float(numValues);
}

void Samples::_1d::Regular::RegularCentered(std::vector<float>& values, size_t numValues)
{
    values.resize(numValues);
    for (size_t i = 0; i < numValues; ++i)
        values[i] = float(i) / float(numValues - 1);
}

void Samples::_1d::Regular::RegularCenteredOffset(std::vector<float>& values, size_t numValues)
{
    float offset = 1.0f / float(numValues * 2);
    values.resize(numValues);
    for (size_t i = 0; i < numValues; ++i)
        values[i] = offset + float(i) / float(numValues);
}
