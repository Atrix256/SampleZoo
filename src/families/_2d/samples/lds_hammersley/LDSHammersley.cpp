/*
FILE: LDSHammersley.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 3/17/2019
*/

#include "codegen.h"

static void VanDerCorput(std::vector<Vec2>& values, size_t base, int axis, bool skipZero, size_t truncateBits)
{
    // figure out how many bits we are working in.
    size_t numValues = values.size();
    size_t value = 1;
    size_t numBits = 0;
    while (value < numValues)
    {
        value *= 2;
        ++numBits;
    }
    size_t numBitsPreserved = numBits - truncateBits;
    size_t bitsPreservedMask = numBitsPreserved > 0 ? (1 << numBitsPreserved) - 1 : 0;

    for (size_t i = 0; i < values.size(); ++i)
    {
        values[i][axis] = 0.0f;
        float denominator = float(base);
        size_t n = i + (skipZero ? 1 : 0);
        n &= bitsPreservedMask;
        while (n > 0)
        {
            size_t multiplier = n % base;
            values[i][axis] += float(multiplier) / denominator;
            n = n / base;
            denominator *= base;
        }
    }
}

void _2d::Samples::LDSHammersley::Hammersley2NoOffset(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    values.resize(numValues);
    VanDerCorput(values, 2, 0, false, 0);
    for (size_t i = 0; i < numValues; ++i)
        values[i][1] = float(i) / float(numValues);
}

void _2d::Samples::LDSHammersley::Hammersley2(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    values.resize(numValues);
    VanDerCorput(values, 2, 0, false, 0);
    float offset = 1.0f / float(numValues * 2);
    for (size_t i = 0; i < numValues; ++i)
        values[i][1] = offset + float(i) / float(numValues);
}

void _2d::Samples::LDSHammersley::Hammersley3(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    values.resize(numValues);
    VanDerCorput(values, 3, 0, false, 0);
    float offset = 1.0f / float(numValues * 2);
    for (size_t i = 0; i < numValues; ++i)
        values[i][1] = offset + float(i) / float(numValues);
}

void _2d::Samples::LDSHammersley::Hammersley5(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    values.resize(numValues);
    VanDerCorput(values, 5, 0, false, 0);
    float offset = 1.0f / float(numValues * 2);
    for (size_t i = 0; i < numValues; ++i)
        values[i][1] = offset + float(i) / float(numValues);
}

void _2d::Samples::LDSHammersley::Hammersley2_1Bit(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    size_t truncatedBits = 1;

    values.resize(numValues);
    VanDerCorput(values, 2, 0, false, truncatedBits);

    size_t value = 1;
    size_t numBits = 0;
    while (value < numValues)
    {
        value *= 2;
        ++numBits;
    }
    size_t multiplier = size_t(1) << truncatedBits;
    float offset = 1.0f / float(numValues * 2);
    for (size_t i = 0; i < numValues; ++i)
        values[i][1] = offset + float(i / multiplier) / float(numValues / multiplier);
}

void _2d::Samples::LDSHammersley::Hammersley2_2Bit(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    size_t truncatedBits = 2;

    values.resize(numValues);
    VanDerCorput(values, 2, 0, false, truncatedBits);

    size_t value = 1;
    size_t numBits = 0;
    while (value < numValues)
    {
        value *= 2;
        ++numBits;
    }
    size_t multiplier = size_t(1) << truncatedBits;
    float offset = 1.0f / float(numValues * 2);
    for (size_t i = 0; i < numValues; ++i)
        values[i][1] = offset + float(i / multiplier) / float(numValues / multiplier);
}

void _2d::Samples::LDSHammersley::Hammersley2_3Bit(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    size_t truncatedBits = 3;

    values.resize(numValues);
    VanDerCorput(values, 2, 0, false, truncatedBits);

    size_t value = 1;
    size_t numBits = 0;
    while (value < numValues)
    {
        value *= 2;
        ++numBits;
    }
    size_t multiplier = size_t(1) << truncatedBits;
    float offset = 1.0f / float(numValues * 2);
    for (size_t i = 0; i < numValues; ++i)
        values[i][1] = offset + float(i / multiplier) / float(numValues / multiplier);
}

void _2d::Samples::LDSHammersley::Hammersley2_4Bit(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    size_t truncatedBits = 4;

    values.resize(numValues);
    VanDerCorput(values, 2, 0, false, truncatedBits);

    size_t value = 1;
    size_t numBits = 0;
    while (value < numValues)
    {
        value *= 2;
        ++numBits;
    }
    size_t multiplier = size_t(1) << truncatedBits;
    float offset = 1.0f / float(numValues * 2);
    for (size_t i = 0; i < numValues; ++i)
        values[i][1] = offset + float(i / multiplier) / float(numValues / multiplier);
}
