/*
FILE: blue_noise.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/12/2019

Description: Randomized sequences that have only high frequency content
*/

#include "codegen.h"
#include <random>
#include <algorithm>

#include <windows.h>

void _1d::Samples::BlueNoise::BestCandidate(std::vector<float>& values, size_t numValues)
{
    // if they want less samples than there are, just truncate the sequence
    if (numValues <= values.size())
    {
        values.resize(numValues);
        return;
    }

    static const size_t c_blueNoiseSampleMultiplier = 1;

    // make sure we use "the good stuff". yes, it matters if the not good stuff gets in, it's a big difference.
    // https://blog.demofox.org/2017/03/15/neural-network-recipe-recognize-handwritten-digits-with-95-accuracy/
    static std::random_device rd("dev/random");
    static std::mt19937 rng(rd());
    static std::uniform_real_distribution<float> dist(0, 1);

    // use whatever samples currently exist, and just add to them, since this is a progressive sequence
    for (size_t i = values.size(); i < numValues; ++i)
    {
        size_t numCandidates = values.size() * c_blueNoiseSampleMultiplier + 1;
        float bestDistance = 0.0f;
        float bestCandidateValue = 0;
        for (size_t candidate = 0; candidate < numCandidates; ++candidate)
        {
            float candidateValue = dist(rng);

            // calculate the closest distance from this point to an existing sample
            float minDist = FLT_MAX;
            for (float value : values)
            {
                float dist = fabsf(candidateValue - value);
                if (dist < minDist)
                    minDist = dist;
            }

            if (minDist > bestDistance)
            {
                bestDistance = minDist;
                bestCandidateValue = candidateValue;
            }
        }
        values.push_back(bestCandidateValue);
    }
}

void _1d::Samples::BlueNoise::BestCandidateRefined(std::vector<float>& values, size_t numValues)
{
    // get the samples
    BestCandidate(values, numValues);
    if (numValues < 2)
        return;

    // get rid of the worst 50% of the samples. sort them to make it faster.
    struct Item
    {
        float value;
        size_t index;
    };
    std::vector<Item> sorted;
    sorted.resize(values.size());
    for (size_t index = 0; index < values.size(); ++index)
    {
        sorted[index].index = index;
        sorted[index].value = values[index];
    }

    std::sort(
        sorted.begin(),
        sorted.end(),
        [] (const Item& a, const Item& b)
        {
            return a.value < b.value;
        }
    );

    while (sorted.size() > numValues / 2)
    {
        // Find and remove the worst point.
        // The worst point is judged by...
        // 1) The point that is closest to a neighbor.
        // 2) Since that point and it's neighbor are tied, kill the one that has a shorter distance to the neighbor on the other side

        float closestDistance = FLT_MAX;
        size_t closestDistancePoint = 0;

        for (size_t searchIndex = 0; searchIndex < sorted.size() - 1; ++searchIndex)
        {
            float distance = sorted[searchIndex + 1].value - sorted[searchIndex].value;
            if (distance < closestDistance)
            {
                closestDistance = distance;
                closestDistancePoint = searchIndex;
            }
        }

        float leftValue = closestDistancePoint > 0 ? sorted[closestDistancePoint - 1].value : 0.0f;
        float leftDistance = sorted[closestDistancePoint].value - leftValue;

        float rightValue = (closestDistancePoint + 2) < sorted.size() ? sorted[closestDistancePoint + 2].value : 1.0f;
        float rightDistance = rightValue - sorted[closestDistancePoint + 1].value;

        size_t removeIndexSorted = (leftValue < rightValue) ? closestDistancePoint : closestDistancePoint + 1;
        size_t removeIndexValues = sorted[removeIndexSorted].index;

        // remove from both arrays
        values.erase(values.begin() + removeIndexValues);
        sorted.erase(sorted.begin() + removeIndexSorted);

        // update reference indices
        for (auto& v : sorted)
        {
            if (v.index >= removeIndexValues)
                v.index--;
        }
    }

    // fill the samples back in
    BestCandidate(values, numValues);
}
