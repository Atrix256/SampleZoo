/*
FILE: uniform_random.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/10/2019
*/

#include "codegen.h"
#include <random>

void Samples::_1d::UniformRandom::UniformRandom(std::vector<float>& values, size_t numValues)
{
    // make sure we use "the good stuff". yes, it matters if the not good stuff gets in, it's a big difference.
    // https://blog.demofox.org/2017/03/15/neural-network-recipe-recognize-handwritten-digits-with-95-accuracy/
    std::random_device rd("dev/random");  
    std::mt19937 rng(rd());
    std::uniform_real_distribution<float> dist(0, 1);

    values.resize(numValues);
    for (size_t i = 0; i < numValues; ++i)
        values[i] = dist(rng);
}
