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
static void DoIntegrationTest(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName, const LAMBDA& lambda, const float c_actual)
{
    static const size_t sampleCount = 1000;

    for (const std::vector<SampleGenerateInfo_1d>& sampleType : sampleFunctions)
    {
        if (sampleType.size() == 0)
            continue;

        std::vector<GraphItem> errors;

        // useful for log graphs
        /*
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
        */

        std::vector<GraphAxisTick> xAxisTicks;
        for (int i = 0; i < 8; ++i)
        {
            int count = int(float(sampleCount) *  (float(i) / 7.0f));

            char buffer[256];
            sprintf(buffer, "%i", count);
            xAxisTicks.push_back({ float(count), buffer, TextHAlign::Right, TextVAlign::Top });
        }

        char fileName[256];
        float globalminy = FLT_MAX;
        float globalmaxy = -FLT_MAX;
        for (const SampleGenerateInfo_1d& sampleFunction : sampleType)
        {
            std::vector<float> samples;
            sampleFunction.function(samples, sampleCount);
            sprintf(fileName, "output/samples/%s/%s/%s_%s.png", sampleFunction.sampleFamily, sampleFunction.sampleType, testName, sampleFunction.name);

            errors.resize(errors.size() + 1);
            GraphItem& error = *errors.rbegin();
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
            yAxisTicks.push_back({ miny, buffer, TextHAlign::Right, TextVAlign::Top });
            sprintf(buffer, "%0.2f", maxy);
            yAxisTicks.push_back({ maxy, buffer, TextHAlign::Right, TextVAlign::Top });
            globalminy = std::min(globalminy, miny);
            globalmaxy = std::max(globalmaxy, maxy);

            // TODO: combine the graphs!
            std::vector<GraphItem> graph;
            graph.push_back(error);
            MakeGraph(fileName, graph, xAxisTicks, yAxisTicks, 512, false, { 0.0f, 0.0f }, { 0.01f, 0.01f });
        }

        if (sampleType.size() == 1)
            continue;

        // put y axis ticks at the min and max y
        std::vector<GraphAxisTick> yAxisTicks;
        char buffer[256];
        sprintf(buffer, "%0.2f", globalminy);
        yAxisTicks.push_back({ globalminy, buffer, TextHAlign::Right, TextVAlign::Center });
        sprintf(buffer, "%0.2f", globalmaxy);
        yAxisTicks.push_back({ globalmaxy, buffer, TextHAlign::Right, TextVAlign::Center });

        sprintf(fileName, "output/samples/%s/%s/%s.png", sampleType[0].sampleFamily, sampleType[0].sampleType, testName);
        MakeGraph(fileName, errors, xAxisTicks, yAxisTicks, 512, false, { 0.0f, 0.0f }, { 0.01f, 0.01f });
    }

    // TODO: 3 graph scopes:
    // 2 - global
    // 1 - sample type
    // 0 - individual (sample function)

    // need another scope for "per sample count"? i dunno... need some way of describing this stuff so the code and auto code / doc gen can pick itup
    // actually, ditch sample counts. let test code decide sample counts needed. can combine numberlines into single image with labels.
}

void Tests::_1d::Integration::Linear(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName)
{
    DoIntegrationTest(sampleFunctions, testName, ::Linear, 0.5f);
}

void Tests::_1d::Integration::Step(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName)
{
    DoIntegrationTest(sampleFunctions, testName, ::Step, 0.5f);
}

void Tests::_1d::Integration::Exp(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName)
{
    DoIntegrationTest(sampleFunctions, testName, ::Exp, e - 1.0f);
}

void Tests::_1d::Integration::Quadratic(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName)
{
    DoIntegrationTest(sampleFunctions, testName, ::Quadratic, 3.0f);
}