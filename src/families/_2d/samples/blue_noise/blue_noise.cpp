/*
FILE: blue_noise.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 3/3/2019
*/

#include "codegen.h"
#include <random>
#include <algorithm>

static void BestCandidateN(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng, const size_t c_blueNoiseSampleMultiplier)
{
    // if they want less samples than there are, just truncate the sequence
    if (numValues <= values.size())
    {
        values.resize(numValues);
        return;
    }

    static std::uniform_real_distribution<float> dist(0, 1);

    for (size_t i = values.size(); i <= numValues; ++i)
    {
        // keep the candidate that is farthest from it's closest point
        size_t numCandidates = values.size() * c_blueNoiseSampleMultiplier + 1;
        float bestDistance = 0.0f;
        Vec2 bestCandidatePos = Vec2{ 0.0f, 0.0f };
        for (size_t candidate = 0; candidate < numCandidates; ++candidate)
        {
            Vec2 candidatePos = Vec2{ dist(rng), dist(rng) };

            // calculate the closest distance from this point to an existing sample
            float minDist = FLT_MAX;
            for (const Vec2& samplePos : values)
            {
                float dist = DistanceUnitTorroidal(samplePos, candidatePos);
                if (dist < minDist)
                    minDist = dist;
            }

            if (minDist > bestDistance)
            {
                bestDistance = minDist;
                bestCandidatePos = candidatePos;
            }
        }
        values.push_back(bestCandidatePos);
    }
}

void _2d::Samples::BlueNoise::BestCandidate(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    BestCandidateN(values, numValues, rng, 1);
}

void _2d::Samples::BlueNoise::BestCandidate5(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    BestCandidateN(values, numValues, rng, 5);
}
