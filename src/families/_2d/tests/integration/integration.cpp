/*
FILE: integration.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 3/4/2019

Description:
Uses samples to integrate 2d functions
*/

#include "codegen.h"
#include "shared/math.h"
#include "shared/graph.h"

static const float c_pi = 3.14159265359f;

static const float c_referenceValue_Disk = 0.5f;
static const float c_referenceValue_Triangle = 0.5f;
static const float c_referenceValue_Step = 1.0f / c_pi;
static const float c_referenceValue_Gaussian = c_pi / 4.0f * (float)erf(1.0) * (float)erf(1.0);
static const float c_referenceValue_Bilinear = 0.25f;

static float SampleImage_Disk(const Vec2& samplePos)
{
    return ((samplePos[0] * samplePos[0] + samplePos[1] * samplePos[1]) < 2.0f / c_pi) ? 1.0f : 0.0f;
}

static float SampleImage_Triangle(const Vec2& samplePos)
{
    return (samplePos[1] > samplePos[0]) ? 1.0f : 0.0f;
}

static float SampleImage_Step(const Vec2& samplePos)
{
    return (samplePos[0] < 1.0f / c_pi) ? 1.0f : 0.0f;
}

static float SampleImage_Gaussian(const Vec2& samplePos)
{
    return expf(-(samplePos[0] * samplePos[0]) - (samplePos[1] * samplePos[1]));
}

static float SampleImage_Bilinear(const Vec2& samplePos)
{
    return samplePos[0] * samplePos[1];
}

template <typename LAMBDA>
static void GetErrorData(const std::vector<Vec2>& samples, GraphItem& error, const LAMBDA& lambda, const float c_actual)
{
    error.data.resize(samples.size());
    float approximation = 0.0f;
    for (size_t index = 0, count = samples.size(); index < count; ++index)
    {
        float z = lambda(samples[index]);
        approximation = Lerp(approximation, z, 1.0f / float(index + 1));
        error.data[index][0] = float(index + 1);
        error.data[index][1] = fabsf(c_actual - approximation) / c_actual;
    }
}

template <typename LAMBDA>
static void DoIntegrationTest(const std::vector<std::vector<SampleGenerateInfo_2d>>& sampleFunctions, const char* testName, const char* fileNamePrefix, const LAMBDA& lambda, const float c_actual)
{
    static const size_t sampleCount = 4096;
    char buffer[256];

    for (const std::vector<SampleGenerateInfo_2d>& sampleType : sampleFunctions)
    {
        if (sampleType.size() == 0)
            continue;

        GraphDesc desc;

        // useful for log graphs
        //put x axis ticks at every power of 10
        int i = 1;
        while (i <= sampleCount)
        {
            sprintf(buffer, "%i", i);
            desc.xAxisTicks.push_back(GraphAxisTick{ float(i), buffer, TextHAlign::Right, TextVAlign::Top });
            i *= 10;
        }

        sprintf(buffer, "%zu", sampleCount);
        desc.xAxisTicks.push_back(GraphAxisTick{ float(sampleCount), buffer, TextHAlign::Right, TextVAlign::Top });

        // useful for non log graphs
        /*
        std::vector<GraphAxisTick> xAxisTicks;
        static int c_numXAxisTicks = 11;
        for (int i = 0; i < c_numXAxisTicks; ++i)
        {
            int count = int(float(sampleCount) *  (float(i) / float(c_numXAxisTicks - 1)));
            if (i == 0)
                count = 1;

            char buffer[256];
            sprintf(buffer, "%i", count);
            xAxisTicks.push_back({ float(count), buffer, TextHAlign::Right, TextVAlign::Top });
        }
        */

        char fileName[256];
        float globalminy = FLT_MAX;
        float globalmaxy = -FLT_MAX;
        for (const SampleGenerateInfo_2d& sampleFunction : sampleType)
        {
            std::vector<Vec2> samples;
            sampleFunction.function(samples, sampleCount, sampleFunction.cacheKey, false);
            sprintf(fileName, "output/%s/samples/%s/%s%s_%s.png", sampleFunction.sampleFamily, sampleFunction.sampleType, fileNamePrefix, testName, sampleFunction.name);

            desc.graphItems.resize(desc.graphItems.size() + 1);
            GraphItem& error = *desc.graphItems.rbegin();
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
            sprintf(buffer, "%0.2f", miny);
            yAxisTicks.push_back({ miny, buffer, TextHAlign::Right, TextVAlign::Top });
            sprintf(buffer, "%0.2f", maxy);
            yAxisTicks.push_back({ maxy, buffer, TextHAlign::Right, TextVAlign::Top });
            globalminy = std::min(globalminy, miny);
            globalmaxy = std::max(globalmaxy, maxy);

            // make the individual graph
            std::vector<GraphItem> graph;
            graph.push_back(error);
            // don't make the individual graphs. they aren't useful
            //MakeGraph(fileName, graph, xAxisTicks, yAxisTicks, 512, false, { 0.0f, 0.0f }, { 0.01f, 0.01f });
        }

        float value = 1.0f;
        for (int i = 1; i <= 7; ++i)
        {
            sprintf(buffer, "10^-%i", i);
            desc.yAxisTicks.push_back({ value, buffer, TextHAlign::Right, TextVAlign::Top });
            value /= 10.0f;
        }

        // make the sample type graph
        sprintf(fileName, "output/%s/samples/%s/%s%s.png", sampleType[0].sampleFamily, sampleType[0].sampleType, fileNamePrefix, testName);
        sprintf(buffer, "Numerical Integration: %s function", testName);

        desc.graphType = GraphType::Points;
        desc.fileName = fileName;
        desc.title = buffer;
        desc.footer = "x axis is sample count, y axis is percent error. Graph is log/log.";
        desc.loglog = true;
        desc.forceYMinMax = true;
        desc.yMinMax = Vec2{ 0.0f, 1.0f };
        MakeGraph(desc);
    }
}

void _2d::Tests::Integration::Disk(const std::vector<std::vector<SampleGenerateInfo_2d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
    DoIntegrationTest(sampleFunctions, testName, fileNamePrefix, SampleImage_Disk, c_referenceValue_Disk);
}

void _2d::Tests::Integration::Triangle(const std::vector<std::vector<SampleGenerateInfo_2d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
    DoIntegrationTest(sampleFunctions, testName, fileNamePrefix, SampleImage_Triangle, c_referenceValue_Triangle);
}

void _2d::Tests::Integration::Step(const std::vector<std::vector<SampleGenerateInfo_2d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
    DoIntegrationTest(sampleFunctions, testName, fileNamePrefix, SampleImage_Step, c_referenceValue_Step);
}

void _2d::Tests::Integration::Gaussian(const std::vector<std::vector<SampleGenerateInfo_2d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
    DoIntegrationTest(sampleFunctions, testName, fileNamePrefix, SampleImage_Gaussian, c_referenceValue_Gaussian);
}

void _2d::Tests::Integration::Bilinear(const std::vector<std::vector<SampleGenerateInfo_2d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
    DoIntegrationTest(sampleFunctions, testName, fileNamePrefix, SampleImage_Bilinear, c_referenceValue_Bilinear);
}
