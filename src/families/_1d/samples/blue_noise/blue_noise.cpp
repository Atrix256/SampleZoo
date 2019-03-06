/*
FILE: blue_noise.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/12/2019

Description: Randomized sequences that have only high frequency content
*/

#include "codegen.h"
#include "manual_test.h"
#include <random>
#include <algorithm>

static void BestCandidateN(std::vector<float>& values, size_t numValues, std::mt19937& rng, const size_t c_blueNoiseSampleMultiplier)
{
    // if they want less samples than there are, just truncate the sequence
    if (numValues <= values.size())
    {
        values.resize(numValues);
        return;
    }

    static std::uniform_real_distribution<float> dist(0, 1);

    // handle the special case of not having any values yet, so we don't check for it in the loops.
    if (values.size() == 0)
        values.push_back(dist(rng));

    // make a sorted list of existing samples
    std::vector<float> sortedValues;
    sortedValues = values;
    sortedValues.reserve(numValues);
    values.reserve(numValues);
    std::sort(sortedValues.begin(), sortedValues.end());

    // use whatever samples currently exist, and just add to them, since this is a progressive sequence
    for (size_t i = values.size(); i < numValues; ++i)
    {
        size_t numCandidates = values.size() * c_blueNoiseSampleMultiplier;
        float bestDistance = 0.0f;
        float bestCandidateValue = 0;
        size_t bestCandidateInsertLocation = 0;
        for (size_t candidate = 0; candidate < numCandidates; ++candidate)
        {
            float candidateValue = dist(rng);

            // binary search the sorted value list to find the values it's closest to.
            auto lowerBound = std::lower_bound(sortedValues.begin(), sortedValues.end(), candidateValue);
            size_t insertLocation = lowerBound - sortedValues.begin();

            // calculate the closest distance (torroidally) from this point to an existing sample by looking left and right.
            float distanceLeft = (insertLocation > 0)
                ? candidateValue - sortedValues[insertLocation - 1]
                : 1.0f + candidateValue - *sortedValues.rbegin();

            float distanceRight = (insertLocation < sortedValues.size())
                ? sortedValues[insertLocation] - candidateValue
                : distanceRight = 1.0f + sortedValues[0] - candidateValue;

            // whichever is closer left vs right is the closer point distance
            float minDist = std::min(distanceLeft, distanceRight);

            // keep the best candidate seen
            if (minDist > bestDistance)
            {
                bestDistance = minDist;
                bestCandidateValue = candidateValue;
                bestCandidateInsertLocation = insertLocation;
            }
        }

        // take the best candidate and also insert it into the sorted values
        sortedValues.insert(sortedValues.begin() + bestCandidateInsertLocation, bestCandidateValue);
        values.push_back(bestCandidateValue);
    }
}

void _1d::Samples::BlueNoise::BestCandidate(std::vector<float>& values, size_t numValues, std::mt19937& rng)
{
    BestCandidateN(values, numValues, rng, 1);
}

void _1d::Samples::BlueNoise::BestCandidate5(std::vector<float>& values, size_t numValues, std::mt19937& rng)
{
    BestCandidateN(values, numValues, rng, 5);
}

void _1d::Samples::BlueNoise::BestCandidate10(std::vector<float>& values, size_t numValues, std::mt19937& rng)
{
    BestCandidateN(values, numValues, rng, 10);
}

/*
void _1d::Samples::BlueNoise::BestCandidateRefined(std::vector<float>& values, size_t numValues, std::mt19937& rng)
{
    // get the samples
    BestCandidate(values, numValues, rng);
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
        // The worst point is judged by the point that if we remove it, the distance between it's left and right neighbor is the smallest

        float worstPointSpan = FLT_MAX;
        size_t worstPointIndex = 0;

        for (size_t searchIndex = 0; searchIndex < sorted.size(); ++searchIndex)
        {
            float left = searchIndex > 0 ? sorted[searchIndex - 1].value : 0.0f;
            float right = searchIndex < sorted.size() - 1 ? sorted[searchIndex + 1].value : 1.0f;

            float distance = right - left;
            if (distance < worstPointSpan)
            {
                worstPointSpan = distance;
                worstPointIndex = searchIndex;
            }
        }

        size_t removeIndexSorted = worstPointIndex;
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
    BestCandidate(values, numValues, rng);
}
*/

void _1d::Samples::BlueNoise::ManualTest()
{
    {
        std::vector<std::vector<SampleGenerateInfo_1d>> testFuncs =
        {
            {
                { [](std::vector<float>& values, size_t numValues, const char* cacheKey, bool wantUnique) {  DataCache::Instance().m_samples__1d.GetSamples_Progressive("blue_noise::BestCandidate", _1d::Samples::BlueNoise::BestCandidate, values, numValues, wantUnique, true); }, "blue_noise::BestCandidate", "_1d", "blue_noise", "BestCandidate", true, true },
                { [](std::vector<float>& values, size_t numValues, const char* cacheKey, bool wantUnique) {  DataCache::Instance().m_samples__1d.GetSamples_NonProgressive("regular::RegularJittered", _1d::Samples::Regular::RegularJittered, values, numValues, wantUnique, true); }, "regular::RegularJittered", "_1d", "regular", "RegularJittered", false, true },
                { [](std::vector<float>& values, size_t numValues, const char* cacheKey, bool wantUnique) {  DataCache::Instance().m_samples__1d.GetSamples_Progressive("uniform_random::UniformRandom", _1d::Samples::UniformRandom::UniformRandom, values, numValues, wantUnique, true); }, "uniform_random::UniformRandom", "_1d", "uniform_random", "UniformRandom", true, true },
                { [](std::vector<float>& values, size_t numValues, const char* cacheKey, bool wantUnique) {  DataCache::Instance().m_samples__1d.GetSamples_Progressive("lds::Sobol", _1d::Samples::LDS::Sobol, values, numValues, wantUnique, false); }, "lds::Sobol", "_1d", "lds", "Sobol", true, false },
                { [](std::vector<float>& values, size_t numValues, const char* cacheKey, bool wantUnique) {  DataCache::Instance().m_samples__1d.GetSamples_NonProgressive("regular::RegularCenteredOffset", _1d::Samples::Regular::RegularCenteredOffset, values, numValues, wantUnique, false); }, "regular::RegularCenteredOffset", "_1d", "regular", "RegularCenteredOffset", false, false },
            }
        };

        _1d::Tests::Discrepancy::CalculateDiscrepancy(testFuncs, "CalculateDiscrepancy", "Doc_");
        //_1d::Tests::Discrepancy::CalculateDiscrepancyWrapAround(testFuncs, "CalculateDiscrepancyWrapAround", "Doc_");
    }

    {
        std::vector<std::vector<SampleGenerateInfo_1d>> testFuncs =
        {
            {
                { [](std::vector<float>& values, size_t numValues, const char* cacheKey, bool wantUnique) {  DataCache::Instance().m_samples__1d.GetSamples_Progressive("blue_noise::BestCandidate", _1d::Samples::BlueNoise::BestCandidate, values, numValues, wantUnique,  true); }, "blue_noise::BestCandidate", "_1d", "blue_noise", "BestCandidate", true, true },
                { [](std::vector<float>& values, size_t numValues, const char* cacheKey, bool wantUnique) {  DataCache::Instance().m_samples__1d.GetSamples_Progressive("uniform_random::UniformRandom", _1d::Samples::UniformRandom::UniformRandom, values, numValues, wantUnique, true); }, "uniform_random::UniformRandom", "_1d", "uniform_random", "UniformRandom", true, true },
                { [](std::vector<float>& values, size_t numValues, const char* cacheKey, bool wantUnique) {  DataCache::Instance().m_samples__1d.GetSamples_Progressive("lds::Sobol", _1d::Samples::LDS::Sobol, values, numValues, wantUnique, false); }, "lds::Sobol", "_1d", "lds", "Sobol", true, false },
                { [](std::vector<float>& values, size_t numValues, const char* cacheKey, bool wantUnique) {  DataCache::Instance().m_samples__1d.GetSamples_NonProgressive("regular::RegularCenteredOffset", _1d::Samples::Regular::RegularCenteredOffset, values, numValues, wantUnique, false); }, "regular::RegularCenteredOffset", "_1d", "regular", "RegularCenteredOffset", false, false },
            }
        };

        _1d::Tests::Integration::Quadratic(testFuncs, "Quadratic", "Doc_");
    }
}
