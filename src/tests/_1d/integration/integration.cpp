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

static void Linear(const std::vector<float>& samples, GraphItem& error)
{
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
}

void Tests::_1d::Integration::Linear(SampleGenerateInfo_1d* sampleFunctions, size_t sampleFunctionCount, size_t* sampleCounts, size_t sampleCountCounts, const char* testName)
{
    std::vector<GraphItem> errors;
    errors.resize(sampleFunctionCount * sampleCountCounts);

    std::vector<GraphAxisTick> xAxisTicks = { {1, "1"}, {10, "10"}, {100, "100"}, {1000, "1000"} };

    char fileName[256];
    for (size_t sampleFunctionIndex = 0; sampleFunctionIndex < sampleFunctionCount; ++sampleFunctionIndex)
    {
        SampleGenerateInfo_1d& sampleFunction = sampleFunctions[sampleFunctionIndex];

        std::vector<float> samples;
        for (size_t sampleCountIndex = 0; sampleCountIndex < sampleCountCounts; ++sampleCountIndex)
        {
            size_t sampleCount = sampleCounts[sampleCountIndex];
            sampleFunction.function(samples, sampleCount);
            sprintf(fileName, "output/samples/%s/%s/%s_%s.png", sampleFunction.sampleFamily, sampleFunction.sampleType, testName, sampleFunction.name);

            GraphItem& error = errors[sampleFunctionIndex * sampleCountCounts + sampleCountIndex];
            error.label = sampleFunction.name;
            ::Linear(samples, error);

            // TODO: combine the graphs!
            std::vector<GraphItem> graph;
            graph.push_back(error);
            MakeGraph(fileName, graph, xAxisTicks, 512, true);
        }
    }

    sprintf(fileName, "output/%s.png", testName);
    MakeGraph(fileName, errors, xAxisTicks, 512, true);

    // TODO: 3 graph scopes:
    // 2 - global
    // 1 - sample type
    // 0 - individual (sample function)

    // need another scope for "per sample count"? i dunno... need some way of describing this stuff so the code and auto code / doc gen can pick itup
    // actually, ditch sample counts. let test code decide sample counts needed. can combine numberlines into single image with labels.
}