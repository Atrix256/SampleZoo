/*
FILE: uniform_random.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 3/3/2019
*/

#include "codegen.h"
#include <random>

void _2d::Samples::UniformRandom::UniformRandom(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    // if they want less samples than there are, just truncate the sequence
    if (numValues <= values.size())
    {
        values.resize(numValues);
        return;
    }

    static std::uniform_real_distribution<float> dist(0, 1);

    // generate random samples
    for (size_t i = values.size(); i < numValues; ++i)
        values.push_back(Vec2{ dist(rng), dist(rng) });
}
