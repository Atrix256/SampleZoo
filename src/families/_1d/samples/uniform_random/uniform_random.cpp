/*
FILE: uniform_random.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/10/2019
*/

#include "codegen.h"
#include <random>

void _1d::Samples::UniformRandom::UniformRandom(std::vector<float>& values, size_t numValues)
{
    // if they want less samples than there are, just truncate the sequence
    if (numValues <= values.size())
    {
        values.resize(numValues);
        return;
    }

    // make sure we use "the good stuff". yes, it matters if the not good stuff gets in, it's a big difference.
    // https://blog.demofox.org/2017/03/15/neural-network-recipe-recognize-handwritten-digits-with-95-accuracy/
    static std::random_device rd("dev/random");
    static std::mt19937 rng(rd());
    static std::uniform_real_distribution<float> dist(0, 1);

    for (size_t i = values.size(); i < numValues; ++i)
        values.push_back(dist(rng));
}
