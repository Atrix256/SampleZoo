/*
FILE: discrepancy.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 3/5/2019

Description:
Calculates metrics about actual point densities vs expected point densitites
*/

#include "codegen.h"
#include <algorithm>
#include <set>
#include "shared/graph.h"

static float CalculateDiscrepancy(const std::vector<Vec2>& samples)
{
     // some info about calculating discrepancy
    // https://math.stackexchange.com/questions/1681562/how-to-calculate-discrepancy-of-a-sequence
 
    // Calculates the discrepancy of this data.
    // Assumes the data is [0,1) for valid sample range.
 
    // Get the sorted list of unique values on each axis
    std::set<float> setSamplesX;
    std::set<float> setSamplesY;
    for (const std::array<float, 2>& sample : samples)
    {
        setSamplesX.insert(sample[0]);
        setSamplesY.insert(sample[1]);
    }
    std::vector<float> sortedXSamples;
    std::vector<float> sortedYSamples;
    sortedXSamples.reserve(setSamplesX.size());
    sortedYSamples.reserve(setSamplesY.size());
    for (float f : setSamplesX)
        sortedXSamples.push_back(f);
    for (float f : setSamplesY)
        sortedYSamples.push_back(f);
 
    // Get the sorted list of samples on the X axis, for faster interval testing
    std::vector<Vec2> sortedSamplesX = samples;
    std::sort(sortedSamplesX.begin(), sortedSamplesX.end(),
        [] (const std::array<float, 2>& itemA, const std::array<float, 2>& itemB)
        {
            return itemA[0] < itemB[0];
        }
    );
 
    // calculate discrepancy
    float maxDifference = 0.0f;
    for (size_t startIndexY = 0; startIndexY <= sortedYSamples.size(); ++startIndexY)
    {
        float startValueY = 0.0f;
        if (startIndexY > 0)
            startValueY = *(sortedYSamples.begin() + startIndexY - 1);
 
        for (size_t startIndexX = 0; startIndexX <= sortedXSamples.size(); ++startIndexX)
        {
            float startValueX = 0.0f;
            if (startIndexX > 0)
                startValueX = *(sortedXSamples.begin() + startIndexX - 1);
 
            for (size_t stopIndexY = startIndexY; stopIndexY <= sortedYSamples.size(); ++stopIndexY)
            {
                float stopValueY = 1.0f;
                if (stopIndexY < sortedYSamples.size())
                    stopValueY = sortedYSamples[stopIndexY];
 
                for (size_t stopIndexX = startIndexX; stopIndexX <= sortedXSamples.size(); ++stopIndexX)
                {
                    float stopValueX = 1.0f;
                    if (stopIndexX < sortedXSamples.size())
                        stopValueX = sortedXSamples[stopIndexX];
 
                    // calculate area
                    float length = stopValueX - startValueX;
                    float height = stopValueY - startValueY;
                    float area = length * height;
 
                    // open interval (startValue, stopValue)
                    size_t countInside = 0;
                    for (const std::array<float, 2>& sample : samples)
                    {
                        if (sample[0] > startValueX &&
                            sample[1] > startValueY &&
                            sample[0] < stopValueX &&
                            sample[1] < stopValueY)
                        {
                            ++countInside;
                        }
                    }
                    float density = float(countInside) / float(samples.size());
                    float difference = std::abs(density - area);
                    if (difference > maxDifference)
                        maxDifference = difference;
 
                    // closed interval [startValue, stopValue]
                    countInside = 0;
                    for (const std::array<float, 2>& sample : samples)
                    {
                        if (sample[0] >= startValueX &&
                            sample[1] >= startValueY &&
                            sample[0] <= stopValueX &&
                            sample[1] <= stopValueY)
                        {
                            ++countInside;
                        }
                    }
                    density = float(countInside) / float(samples.size());
                    difference = std::abs(density - area);
                    if (difference > maxDifference)
                        maxDifference = difference;
                }
            }
        }
    }
 
    return maxDifference;
}

void _2d::Tests::Discrepancy::CalculateDiscrepancy(const std::vector<std::vector<SampleGenerateInfo_2d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
    static const int c_sampleCount = 64;

    for (const std::vector<SampleGenerateInfo_2d>& sampleType : sampleFunctions)
    {
        if (sampleType.size() == 0)
            continue;

        float minDiscrepancy = FLT_MAX;
        float maxDiscrepancy = -FLT_MAX;

        GraphDesc desc;

        for (int sampleCount = 0; sampleCount <= c_sampleCount; sampleCount += 4)
        {
            char buffer[256];
            sprintf(buffer, "%i", sampleCount > 0 ? sampleCount : 1);
            desc.xAxisTicks.push_back({ float(sampleCount > 0 ? sampleCount : 1), buffer, TextHAlign::Right, TextVAlign::Top });
        }

        for (const SampleGenerateInfo_2d& sampleFunction : sampleType)
        {
            std::vector<Vec2> samples;

            desc.graphItems.resize(desc.graphItems.size() + 1);
            GraphItem& discrepancy = *desc.graphItems.rbegin();
            discrepancy.label = sampleFunction.name;
            for (int sampleCount = 1; sampleCount <= c_sampleCount; ++sampleCount)
            {
                sampleFunction.function(samples, sampleCount, sampleFunction.cacheKey, false);
                float d = ::CalculateDiscrepancy(samples);
                minDiscrepancy = std::min(minDiscrepancy, d);
                maxDiscrepancy = std::max(maxDiscrepancy, d);
                discrepancy.data.push_back(Vec2{float(sampleCount), d});
            }
        }

        desc.yAxisTicks.push_back({ 0.0f, "0.0", TextHAlign::Right, TextVAlign::Bottom });
        desc.yAxisTicks.push_back({ 1.0f, "1.0", TextHAlign::Right, TextVAlign::Top });

        // make the sample type graph
        char fileName[256];
        sprintf(fileName, "output/%s/samples/%s/%s%s.png", sampleType[0].sampleFamily, sampleType[0].sampleType, fileNamePrefix, testName);

        desc.fileName = fileName;
        desc.footer = "x axis is sample count, y axis is discrepancy.";
        desc.title = "Discrepancy";
        desc.forceYMinMax = true;
        desc.yMinMax = Vec2{ 0.0f, 1.0f };
        MakeGraph(desc);
    }
}
