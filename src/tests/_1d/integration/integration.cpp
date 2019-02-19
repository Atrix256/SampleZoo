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

static const float e = 2.71828182845904523536f;

static float Linear(float x)
{
    // function:  y = x
    return x;
}

static float Step(float x)
{
    // function:  y = (x > 0.5) ? 1 : 0
    return x > 0.5f ? 1.0f : 0.0f;
}

static float Exp(float x)
{
    // function:  y = e^x
    return expf(x);
}

static float Quadratic(float x)
{
    // function: y = 3x^2+2x+1
    return 3.0f*x*x + 2.0f*x + 1.0f;
}

template <typename LAMBDA>
static void GetErrorData(const std::vector<float>& samples, GraphItem& error, const LAMBDA& lambda, const float c_actual)
{
    error.data.resize(samples.size());
    float approximation = 0.0f;
    for (size_t index = 0, count = samples.size(); index < count; ++index)
    {
        float y = lambda(samples[index]);
        approximation = Lerp(approximation, y, 1.0f / float(index + 1));
        error.data[index][0] = float(index + 1);
        error.data[index][1] = fabsf(c_actual - approximation);
    }
}

template <typename LAMBDA>
static void DoIntegrationTest(SampleGenerateInfo_1d* sampleFunctions, size_t sampleFunctionCount, const char* testName, const LAMBDA& lambda, const float c_actual)
{
    std::vector<GraphItem> errors;
    errors.resize(sampleFunctionCount);

    static const size_t sampleCount = 1000;

    //put x axis ticks at every power of 10
    std::vector<GraphAxisTick> xAxisTicks;
    int i = 1;
    while (i <= sampleCount)
    {
        char buffer[256];
        sprintf(buffer, "%i", i);
        xAxisTicks.push_back({ float(i), buffer, TextHAlign::Right, TextVAlign::Top });
        i *= 10;
    }

    char fileName[256];
    float globalminy = FLT_MAX;
    float globalmaxy = -FLT_MAX;
    for (size_t sampleFunctionIndex = 0; sampleFunctionIndex < sampleFunctionCount; ++sampleFunctionIndex)
    {
        SampleGenerateInfo_1d& sampleFunction = sampleFunctions[sampleFunctionIndex];

        std::vector<float> samples;
        sampleFunction.function(samples, sampleCount);
        sprintf(fileName, "output/samples/%s/%s/%s_%s.png", sampleFunction.sampleFamily, sampleFunction.sampleType, testName, sampleFunction.name);

        GraphItem& error = errors[sampleFunctionIndex];
        error.label = sampleFunction.name;
        GetErrorData(samples, error, lambda, c_actual);

        // put y axis ticks at the min and max y
        std::vector<GraphAxisTick> yAxisTicks;
        float miny = FLT_MAX;
        float maxy = -FLT_MAX;
        for (Vec2& v : error.data)
        {
            miny = std::min(miny, v[1]);
            maxy = std::max(maxy, v[1]);
        }
        char buffer[256];
        sprintf(buffer, "%0.2f", miny);
        yAxisTicks.push_back({ miny, buffer, TextHAlign::Right, TextVAlign::Center });
        sprintf(buffer, "%0.2f", maxy);
        yAxisTicks.push_back({ maxy, buffer, TextHAlign::Right, TextVAlign::Center });
        globalminy = std::min(globalminy, miny);
        globalmaxy = std::max(globalmaxy, maxy);

        // TODO: combine the graphs!
        std::vector<GraphItem> graph;
        graph.push_back(error);
        MakeGraph(fileName, graph, xAxisTicks, yAxisTicks, 512, true, { 0.0f, 0.0f }, { 0.25f, 0.25f });
    }

    // put y axis ticks at the min and max y
    std::vector<GraphAxisTick> yAxisTicks;
    char buffer[256];
    sprintf(buffer, "%0.2f", globalminy);
    yAxisTicks.push_back({ globalminy, buffer, TextHAlign::Right, TextVAlign::Center });
    sprintf(buffer, "%0.2f", globalmaxy);
    yAxisTicks.push_back({ globalmaxy, buffer, TextHAlign::Right, TextVAlign::Center });

    sprintf(fileName, "output/%s.png", testName);
    MakeGraph(fileName, errors, xAxisTicks, yAxisTicks, 512, true, { 0.0f, 0.0f }, { 0.25f, 0.25f });

    // TODO: 3 graph scopes:
    // 2 - global
    // 1 - sample type
    // 0 - individual (sample function)

    // need another scope for "per sample count"? i dunno... need some way of describing this stuff so the code and auto code / doc gen can pick itup
    // actually, ditch sample counts. let test code decide sample counts needed. can combine numberlines into single image with labels.
}

void Tests::_1d::Integration::Linear(SampleGenerateInfo_1d* sampleFunctions, size_t sampleFunctionCount, const char* testName)
{
    DoIntegrationTest(sampleFunctions, sampleFunctionCount, testName, ::Linear, 0.5f);
}

void Tests::_1d::Integration::Step(SampleGenerateInfo_1d* sampleFunctions, size_t sampleFunctionCount, const char* testName)
{
    DoIntegrationTest(sampleFunctions, sampleFunctionCount, testName, ::Step, 0.5f);
}

void Tests::_1d::Integration::Exp(SampleGenerateInfo_1d* sampleFunctions, size_t sampleFunctionCount, const char* testName)
{
    DoIntegrationTest(sampleFunctions, sampleFunctionCount, testName, ::Exp, e - 1.0f);
}

void Tests::_1d::Integration::Quadratic(SampleGenerateInfo_1d* sampleFunctions, size_t sampleFunctionCount, const char* testName)
{
    DoIntegrationTest(sampleFunctions, sampleFunctionCount, testName, ::Quadratic, 3.0f);
}