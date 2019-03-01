/*
FILE: shuffle.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 3/1/2019

Description:
tests to see how well a number sequence would do as a shuffle.
*/

#include "codegen.h"
#include "shared/graph.h"

static int const c_numShuffleDraws = 64; // the number of items to draw from the shuffle

void HistogramN(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName, const char* fileNamePrefix, const int c_numItems)
{
    GraphDesc desc;
}

void ValuesN(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName, const char* fileNamePrefix, const int c_numItems)
{
    for (const std::vector<SampleGenerateInfo_1d>& sampleType : sampleFunctions)
    {
        if (sampleType.size() == 0)
            continue;

        for (const SampleGenerateInfo_1d& sampleFunction : sampleType)
        {
            GraphDesc desc;

            std::vector<float> samples;

            desc.graphItems.resize(desc.graphItems.size() + 1);
            GraphItem& graph = *desc.graphItems.rbegin();
            graph.label = sampleFunction.name;
            sampleFunction.function(samples, c_numShuffleDraws, sampleFunction.cacheKey, false);
            for (int sampleCount = 0; sampleCount < c_numShuffleDraws; ++sampleCount)
            {
                int item = int(samples[sampleCount] * float(c_numItems - 1) + 0.5f);
                graph.data.push_back(Vec2{ float(sampleCount + 1), float(item) });
            }

            // make the sample type graph
            char fileName[256];
            sprintf(fileName, "output/%s/samples/%s/%s_%s.png", sampleFunction.sampleFamily, sampleFunction.sampleType, testName, sampleFunction.name);

            desc.fileName = fileName;
            desc.footer = "x axis is sample index, y is the shuffle item";
            char title[256];
            sprintf(title, "Shuffling %i items", c_numItems);
            desc.title = title;
            desc.forceYMinMax = true;
            desc.yMinMax = Vec2{ 0.0f, float(c_numItems - 1) };
            MakeGraph(desc);
        }
    }
}

void _1d::Tests::Shuffle::Histogram(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
    HistogramN(sampleFunctions, testName, fileNamePrefix, 16);
}

void _1d::Tests::Shuffle::Values(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
    ValuesN(sampleFunctions, testName, fileNamePrefix, 16);
}
