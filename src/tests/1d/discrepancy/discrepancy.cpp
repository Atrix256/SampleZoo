/*
FILE: discrepancy.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019

Description:
Calculates metrics about actual point densities vs expected point densitites
*/

#include "discrepancy.h"
#include <algorithm>

float Tests::_1d::Discrepancy::CalculateDiscrepancy(const std::vector<float>& samples)
{
    // some info about calculating discrepancy
    // https://math.stackexchange.com/questions/1681562/how-to-calculate-discrepancy-of-a-sequence
 
    // Calculates the discrepancy of this data.
    // Assumes the data is [0,1) for valid sample range
    std::vector<float> sortedSamples = samples;
    std::sort(sortedSamples.begin(), sortedSamples.end());
 
    float maxDifference = 0.0f;
    for (size_t startIndex = 0; startIndex <= samples.size(); ++startIndex)
    {
        // startIndex 0 = 0.0f.  startIndex 1 = sortedSamples[0]. etc
 
        float startValue = 0.0f;
        if (startIndex > 0)
            startValue = sortedSamples[startIndex - 1];
 
        for (size_t stopIndex = startIndex; stopIndex <= samples.size(); ++stopIndex)
        {
            // stopIndex 0 = sortedSamples[0].  startIndex[N] = 1.0f. etc
 
            float stopValue = 1.0f;
            if (stopIndex < samples.size())
                stopValue = sortedSamples[stopIndex];
 
            float length = stopValue - startValue;
 
            // open interval (startValue, stopValue)
            size_t countInside = 0;
            for (float sample : samples)
            {
                if (sample > startValue &&
                    sample < stopValue)
                {
                    ++countInside;
                }
            }
            float density = float(countInside) / float(samples.size());
            float difference = std::abs(density - length);
            if (difference > maxDifference)
                maxDifference = difference;
 
            // closed interval [startValue, stopValue]
            countInside = 0;
            for (float sample : samples)
            {
                if (sample >= startValue &&
                    sample <= stopValue)
                {
                    ++countInside;
                }
            }
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