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

void Tests::_1d::Discrepancy::CalculateDiscrepancy(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName)
{
    static const int c_sampleCount = 64;

    std::vector<GraphAxisTick> xAxisTicks;
    for (int sampleCount = 0; sampleCount <= c_sampleCount; sampleCount += 4)
    {
        char buffer[256];
        sprintf(buffer, "%i", sampleCount > 0 ? sampleCount : 1);
        xAxisTicks.push_back({ float(sampleCount > 0 ? sampleCount : 1), buffer, TextHAlign::Right, TextVAlign::Top });
    }

    for (const std::vector<SampleGenerateInfo_1d>& sampleType : sampleFunctions)
    {
        if (sampleType.size() == 0)
            continue;

        float minDiscrepancy = FLT_MAX;
        float maxDiscrepancy = -FLT_MAX;

        std::vector<GraphItem> discrepancies;
        for (const SampleGenerateInfo_1d& sampleFunction : sampleType)
        {
            std::vector<float> samples;

            discrepancies.resize(discrepancies.size() + 1);
            GraphItem& discrepancy = *discrepancies.rbegin();
            discrepancy.label = sampleFunction.name;
            for (int sampleCount = 1; sampleCount <= c_sampleCount; ++sampleCount)
            {
                sampleFunction.function(samples, sampleCount);
                float d = ::CalculateDiscrepancy(samples);
                minDiscrepancy = std::min(minDiscrepancy, d);
                maxDiscrepancy = std::max(maxDiscrepancy, d);
                discrepancy.data.push_back(Vec2{float(sampleCount), d});
            }
        }

        std::vector<GraphAxisTick> yAxisTicks;
        char buffer[256];
        sprintf(buffer, "%0.2f", minDiscrepancy);
        yAxisTicks.push_back({ minDiscrepancy, buffer, TextHAlign::Right, TextVAlign::Bottom });
        sprintf(buffer, "%0.2f", maxDiscrepancy);
        yAxisTicks.push_back({ maxDiscrepancy, buffer, TextHAlign::Right, TextVAlign::Top });

        // make the sample type graph
        char fileName[256];
        sprintf(fileName, "output/samples/%s/%s/%s.png", sampleType[0].sampleFamily, sampleType[0].sampleType, testName);
        const char* footer = "x axis is sample count, y axis is discrepancy.";
        MakeGraph(GraphType::Lines, fileName, "Discrepancy", footer, discrepancies, xAxisTicks, yAxisTicks, 512, false, { 0.0f, 0.0f }, { 0.0f, 0.0f });
    }
}

void Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName)
{
    static const int c_sampleCount = 64;

    std::vector<GraphAxisTick> xAxisTicks;
    for (int sampleCount = 0; sampleCount <= c_sampleCount; sampleCount += 4)
    {
        char buffer[256];
        sprintf(buffer, "%i", sampleCount > 0 ? sampleCount : 1);
        xAxisTicks.push_back({ float(sampleCount > 0 ? sampleCount : 1), buffer, TextHAlign::Right, TextVAlign::Top });
    }

    for (const std::vector<SampleGenerateInfo_1d>& sampleType : sampleFunctions)
    {
        if (sampleType.size() == 0)
            continue;

        float minDiscrepancy = FLT_MAX;
        float maxDiscrepancy = -FLT_MAX;

        std::vector<GraphItem> discrepancies;
        for (const SampleGenerateInfo_1d& sampleFunction : sampleType)
        {
            std::vector<float> samples;

            discrepancies.resize(discrepancies.size() + 1);
            GraphItem& discrepancy = *discrepancies.rbegin();
            discrepancy.label = sampleFunction.name;
            for (int sampleCount = 1; sampleCount <= c_sampleCount; ++sampleCount)
            {
                sampleFunction.function(samples, sampleCount);
                float d = ::CalculateDiscrepancyWrapAround(samples);
                minDiscrepancy = std::min(minDiscrepancy, d);
                maxDiscrepancy = std::max(maxDiscrepancy, d);
                discrepancy.data.push_back(Vec2{float(sampleCount), d});
            }
        }

        std::vector<GraphAxisTick> yAxisTicks;
        char buffer[256];
        sprintf(buffer, "%0.2f", minDiscrepancy);
        yAxisTicks.push_back({ minDiscrepancy, buffer, TextHAlign::Right, TextVAlign::Bottom });
        sprintf(buffer, "%0.2f", maxDiscrepancy);
        yAxisTicks.push_back({ maxDiscrepancy, buffer, TextHAlign::Right, TextVAlign::Top });

        // make the sample type graph
        char fileName[256];
        sprintf(fileName, "output/samples/%s/%s/%s.png", sampleType[0].sampleFamily, sampleType[0].sampleType, testName);
        const char* footer = "x axis is sample count, y axis is discrepancy.";
        MakeGraph(GraphType::Lines, fileName, "Torroidal Discrepancy", footer, discrepancies, xAxisTicks, yAxisTicks, 512, false, { 0.0f, 0.0f }, { 0.0f, 0.0f });
    }
}