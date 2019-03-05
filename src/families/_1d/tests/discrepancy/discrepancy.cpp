/*
FILE: discrepancy.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019

Description:
Calculates metrics about actual point densities vs expected point densitites
*/

#include "codegen.h"
#include <algorithm>
#include "shared/graph.h"

static float CalculateDiscrepancy(const std::vector<float>& samples)
{
    // one sample without wrap around:
    // whichever is larger between the sample and 1.0f - the sample. That is the larger empty area.
    if (samples.size() == 1)
        return std::max(samples[0], 1.0f - samples[0]);

    // sort the samples, but add a 0.0 and a 1.0 to represent the "hard walls" on the left and right
    // since this isn't torroidal
    std::vector<float> sortedSamples = samples;
    sortedSamples.push_back(0.0f);
    sortedSamples.push_back(1.0f);
    std::sort(sortedSamples.begin(), sortedSamples.end());

    float maxDifference = 0.0f;
    for (size_t startIndex = 0; startIndex < sortedSamples.size(); ++startIndex)
    {
        float startValue = sortedSamples[startIndex];

        for (size_t stopIndex = startIndex + 1; stopIndex < sortedSamples.size(); ++stopIndex)
        {
            float stopValue = sortedSamples[stopIndex];

            float length = stopValue - startValue;

            // open interval (startValue, stopValue)
            size_t countInside = stopIndex - startIndex - 1;
            float density = float(countInside) / float(samples.size());
            float difference = std::abs(density - length);
            if (difference > maxDifference)
                maxDifference = difference;

            // closed interval [startValue, stopValue], but don't count the very first or last sample,
            // since they are the "hard walls", and not actually sample points.
            if (startIndex > 0)
                countInside += 1;
            if (stopIndex < sortedSamples.size() - 1)
                countInside += 1;
            density = float(countInside) / float(samples.size());
            difference = std::abs(density - length);
            if (difference > maxDifference)
                maxDifference = difference;

        }
    }
    return maxDifference;
}

static float CalculateDiscrepancyWrapAround(const std::vector<float>& samples)
{
    // one sample with wrap around:
    // there is a region 1.0 in size minus the size of an infintessimal point that is completely empty.
    if (samples.size() == 1)
        return 1.0f;

    // Calculates the torroidal discrepancy of this data.
    std::vector<float> sortedSamples = samples;
    std::sort(sortedSamples.begin(), sortedSamples.end());

    float maxDifference = 0.0f;
    for (size_t startIndex = 0; startIndex < samples.size(); ++startIndex)
    {
        float startValue = sortedSamples[startIndex];

        for (size_t stopOffset = 1; stopOffset < samples.size(); ++stopOffset)
        {
            size_t stopIndex = (startIndex + stopOffset) % samples.size();

            float stopValue = sortedSamples[stopIndex];

            float length = stopValue - startValue;
            if (length < 0.0f)
                length = 1.0f + length;

            // open interval (startValue, stopValue), but torroidally
            size_t countInside;
            if (stopIndex > startIndex)
                countInside = stopIndex - startIndex - 1;
            else
                countInside = (samples.size() + stopIndex) - startIndex - 1;
            float density = float(countInside) / float(samples.size());
            float difference = std::abs(density - length);
            if (difference > maxDifference)
                maxDifference = difference;

            // closed interval [startValue, stopValue], but toroidally
            countInside += 2;
            density = float(countInside) / float(samples.size());
            difference = std::abs(density - length);
            if (difference > maxDifference)
                maxDifference = difference;
        }
    }
    return maxDifference;
}

void _1d::Tests::Discrepancy::CalculateDiscrepancy(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
    static const int c_sampleCount = 64;

    for (const std::vector<SampleGenerateInfo_1d>& sampleType : sampleFunctions)
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

        for (const SampleGenerateInfo_1d& sampleFunction : sampleType)
        {
            std::vector<float> samples;

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

/*
void _1d::Tests::Discrepancy::CalculateDiscrepancyWrapAround(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
    static const int c_sampleCount = 64;

    for (const std::vector<SampleGenerateInfo_1d>& sampleType : sampleFunctions)
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

        for (const SampleGenerateInfo_1d& sampleFunction : sampleType)
        {
            std::vector<float> samples;

            desc.graphItems.resize(desc.graphItems.size() + 1);
            GraphItem& discrepancy = *desc.graphItems.rbegin();
            discrepancy.label = sampleFunction.name;
            for (int sampleCount = 1; sampleCount <= c_sampleCount; ++sampleCount)
            {
                sampleFunction.function(samples, sampleCount, sampleFunction.cacheKey, false);
                float d = ::CalculateDiscrepancyWrapAround(samples);
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
        const char* footer = "x axis is sample count, y axis is discrepancy.";

        desc.fileName = fileName;
        desc.footer = "x axis is sample count, y axis is discrepancy.";
        desc.title = "Torroidal Discrepancy";
        desc.forceYMinMax = true;
        desc.yMinMax = Vec2{ 0.0f, 1.0f };
        MakeGraph(desc);
    }
}
*/