/*
FILE: integration.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/13/2019

Description:
Uses samples to integrate 1d functions
*/

#include "codegen.h"
#include "shared/math.h"

void Tests::_1d::Integration::Linear(SampleGenerate_1d* sampleFunctions, size_t sampleFunctionCount, size_t* sampleCounts, size_t sampleCountCounts)
{
    /*
    error.resize(samples.size());

    // function:  y = x
    auto f = [](float x)
    {
        return x;
    };
    static const float c_actual = 0.5f;
    float approximation = 0.0f;
    for (size_t index = 0, count = samples.size(); index < count; ++index)
    {
        float y = f(samples[index]);
        approximation = Lerp(approximation, y, 1.0f / float(index + 1));
        error[index] = fabsf(c_actual - approximation);
    }
    */
}