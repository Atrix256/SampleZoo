/*
FILE: blue_noise.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/12/2019

Description: Randomized sequences that have only high frequency content
*/

#include "codegen.h"
#include <random>

void Samples::_1d::BlueNoise::BestCandidate(std::vector<float>& values, size_t numValues)
{
    static const size_t c_blueNoiseSampleMultiplier = 1;

    // make sure we use "the good stuff". yes, it matters if the not good stuff gets in, it's a big difference.
    // https://blog.demofox.org/2017/03/15/neural-network-recipe-recognize-handwritten-digits-with-95-accuracy/
    std::random_device rd("dev/random");
    std::mt19937 rng(rd());
    std::uniform_real_distribution<float> dist(0, 1);

    values.resize(numValues);
    size_t sampleInt = 0;
    for (size_t i = 0; i < numValues; ++i)
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
        values[i] = bestCandidateValue;
    }
}
