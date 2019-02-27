/*
FILE: uniform_random.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/10/2019
*/

#include "codegen.h"
#include <random>

void _1d::Samples::UniformRandom::UniformRandom(std::vector<float>& values, size_t numValues, const char* cacheKey)
{
    // if they want less samples than there are, just truncate the sequence
    if (numValues <= values.size())
    {
        values.resize(numValues);
        return;
    }

    // get random number generator
    std::mt19937 rng = DataCache::Instance().m_rngSeeds.GetRNG(cacheKey);
    static std::uniform_real_distribution<float> dist(0, 1);

    // generate random samples
    for (size_t i = values.size(); i < numValues; ++i)
        values.push_back(dist(rng));
}
