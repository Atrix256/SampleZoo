/*
FILE: discrepancy.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019

Description:
Calculates metrics about actual point densities vs expected point densitites
*/

#include "codegen.h"
#include <algorithm>

float Tests::_1d::Discrepancy::CalculateDiscrepancy(const std::vector<float>& samples)
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

float Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(const std::vector<float>& samples)
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