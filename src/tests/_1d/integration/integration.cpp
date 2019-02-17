/*
FILE: integration.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/13/2019

Description:
Uses samples to integrate 1d functions
*/

#include "codegen.h"
#include "shared/math.h"
#include "shared/graph.h"

static void Linear(const char* fileName, const std::vector<float>& samples, int width, const char* functionName)
{
    GraphItem error;
    error.label = functionName;
    error.data.resize(samples.size());

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
        error.data[index][0] = float(index);
        error.data[index][1] = fabsf(c_actual - approximation);
    }

    // TODO: combine the graphs!
    std::vector<GraphItem> graph;
    graph.push_back(error);
    MakeGraph(fileName, graph, width);
}

void Tests::_1d::Integration::Linear(SampleGenerateInfo_1d* sampleFunctions, size_t sampleFunctionCount, size_t* sampleCounts, size_t sampleCountCounts, const char* testName)
{
    char fileName[256];
    for (size_t sampleFunctionIndex = 0; sampleFunctionIndex < sampleFunctionCount; ++sampleFunctionIndex)
    {
        SampleGenerateInfo_1d& sampleFunction = sampleFunctions[sampleFunctionIndex];

        std::vector<float> samples;
        for (size_t sampleCountIndex = 0; sampleCountIndex < sampleCountCounts; ++sampleCountIndex)
        {
            size_t sampleCount = sampleCounts[sampleCountIndex];
            sampleFunction.function(samples, sampleCount);
            sprintf(fileName, "output/samples/%s/%s/%s_%s_%zu.png", sampleFunction.sampleFamily, sampleFunction.sampleType, testName, sampleFunction.name, sampleCount);
            ::Linear(fileName, samples, 512, sampleFunction.name);
        }
    }
}