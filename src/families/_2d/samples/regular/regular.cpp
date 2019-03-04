/*
FILE: regular.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 3/4/2019
*/

#include "codegen.h"
#include <random>

void _2d::Samples::Regular::Regular(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    size_t sizeX = size_t(sqrtf(numValues));
    size_t sizeY = numValues / sizeX;

    values.resize(numValues, Vec2{ 0.0f, 0.0f });
    int i = 0;
    for (size_t iy = 0; iy < sizeY; ++iy)
    {
        for (size_t ix = 0; ix < sizeX; ++ix)
        {
            values[i][0] = float(ix) / float(sizeX);
            values[i][1] = float(iy) / float(sizeY);
            ++i;
        }
    }
}

void _2d::Samples::Regular::RegularCentered(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    size_t sizeX = size_t(sqrtf(numValues));
    size_t sizeY = numValues / sizeX;

    values.resize(numValues, Vec2{ 0.0f, 0.0f });
    int i = 0;
    for (size_t iy = 0; iy < sizeY; ++iy)
    {
        for (size_t ix = 0; ix < sizeX; ++ix)
        {
            values[i][0] = float(ix) / float(sizeX - 1);
            values[i][1] = float(iy) / float(sizeY - 1);
            ++i;
        }
    }
}

void _2d::Samples::Regular::RegularCenteredOffset(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    size_t sizeX = size_t(sqrtf(numValues));
    size_t sizeY = numValues / sizeX;

    float offsetX = 1.0f / float(sizeX * 2);
    float offsetY = 1.0f / float(sizeY * 2);

    values.resize(numValues, Vec2{ 0.0f, 0.0f });
    int i = 0;
    for (size_t iy = 0; iy < sizeY; ++iy)
    {
        for (size_t ix = 0; ix < sizeX; ++ix)
        {
            values[i][0] = offsetX + float(ix) / float(sizeX);
            values[i][1] = offsetY + float(iy) / float(sizeY);
            ++i;
        }
    }
}

void _2d::Samples::Regular::RegularJittered(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    size_t sizeX = size_t(sqrtf(numValues));
    size_t sizeY = numValues / sizeX;

    std::uniform_real_distribution<float> distX(0.0f, 1.0f / float(sizeX));
    std::uniform_real_distribution<float> distY(0.0f, 1.0f / float(sizeY));

    values.resize(numValues, Vec2{ 0.0f, 0.0f });
    int i = 0;
    for (size_t iy = 0; iy < sizeY; ++iy)
    {
        for (size_t ix = 0; ix < sizeX; ++ix)
        {
            values[i][0] = distX(rng) + float(ix) / float(sizeX);
            values[i][1] = distY(rng) + float(iy) / float(sizeY);
            ++i;
        }
    }
}
