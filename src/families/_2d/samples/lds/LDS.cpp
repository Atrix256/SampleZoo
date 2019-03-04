/*
FILE: LDS.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 3/4/2019
*/

#include "codegen.h"

static void Hammersley(std::vector<Vec2>& values, size_t numValues, size_t truncateBits)
{
    // figure out how many bits we are working in.
    size_t value = 1;
    size_t numBits = 0;
    while (value < numValues)
    {
        value *= 2;
        ++numBits;
    }

    // calculate the sample points
    values.resize(numValues);
    size_t sampleInt = 0;
    for (size_t i = 0; i < numValues; ++i)
    {
        // x axis
        values[i][0] = 0.0f;
        {
            size_t n = i >> truncateBits;
            float base = 1.0f / 2.0f;
            while (n)
            {
                if (n & 1)
                    values[i][0] += base;
                n /= 2;
                base /= 2.0f;
            }
        }

        // y axis
        values[i][1] = 0.0f;
        {
            size_t n = i >> truncateBits;
            size_t mask = size_t(1) << (numBits - 1 - truncateBits);

            float base = 1.0f / 2.0f;
            while (mask)
            {
                if (n & mask)
                    values[i][1] += base;
                mask /= 2;
                base /= 2.0f;
            }
        }
    }
}

static void Halton(std::vector<Vec2>& values, size_t numValues, size_t baseX, size_t baseY, bool skipZero = true)
{
    values.resize(numValues);

    // calculate the sample points
    for (size_t i = 0; i < numValues; ++i)
    {
        // x axis
        values[i][0] = 0.0f;
        {
            float denominator = float(baseX);
            size_t n = i + (skipZero ? 1 : 0);
            while (n > 0)
            {
                size_t multiplier = n % baseX;
                values[i][0] += float(multiplier) / denominator;
                n = n / baseX;
                denominator *= float(baseX);
            }
        }

        // y axis
        values[i][1] = 0.0f;
        {
            float denominator = float(baseY);
            size_t n = i + (skipZero ? 1 : 0);
            while (n > 0)
            {
                size_t multiplier = n % baseY;
                values[i][1] += float(multiplier) / denominator;
                n = n / baseY;
                denominator *= float(baseY);
            }
        }
    }
}

static size_t Ruler(size_t n)
{
    size_t ret = 0;
    while (n != 0 && (n & 1) == 0)
    {
        n /= 2;
        ++ret;
    }
    return ret;
}

void _2d::Samples::LDS::Sobol(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    // x axis
    values.resize(numValues);
    size_t sampleInt = 0;
    for (size_t i = 0; i < numValues; ++i)
    {
        size_t ruler = Ruler(i + 1);
        size_t direction = size_t(size_t(1) << size_t(31 - ruler));
        sampleInt = sampleInt ^ direction;
        values[i][0] = float(sampleInt) / std::pow(2.0f, 32.0f);
    }

    // y axis
    // Code adapted from http://web.maths.unsw.edu.au/~fkuo/sobol/
    // uses numbers: new-joe-kuo-6.21201

    // Direction numbers
    std::vector<size_t> V;
    V.resize((size_t)ceil(log((double)numValues) / log(2.0)));
    V[0] = size_t(1) << size_t(31);
    for (size_t i = 1; i < V.size(); ++i)
        V[i] = V[i - 1] ^ (V[i - 1] >> 1);

    // Samples
    sampleInt = 0;
    for (size_t i = 0; i < numValues; ++i) {
        size_t ruler = Ruler(i + 1);
        sampleInt = sampleInt ^ V[ruler];
        values[i][1] = float(sampleInt) / std::pow(2.0f, 32.0f);
    }
}

void _2d::Samples::LDS::Halton_2_3_Zero(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    Halton(values, numValues, 2, 3, false);
}

void _2d::Samples::LDS::Halton_2_3(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    Halton(values, numValues, 2, 3);
}

void _2d::Samples::LDS::Halton_5_7(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    Halton(values, numValues, 5, 7);
}

void _2d::Samples::LDS::Halton_13_9(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    Halton(values, numValues, 13, 9);
}

void _2d::Samples::LDS::Hammersley(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    ::Hammersley(values, numValues, 0);
}

void _2d::Samples::LDS::Hammersley_1Bit(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    ::Hammersley(values, numValues, 1);
}

void _2d::Samples::LDS::Hammersley_2Bits(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    ::Hammersley(values, numValues, 2);
}

void _2d::Samples::LDS::NRooks(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    // make N rooks that can't see each other on x or y axis
    std::vector<size_t> rookPositions(numValues, 0);
    for (size_t i = 0; i < numValues; ++i)
        rookPositions[i] = i;
    std::shuffle(rookPositions.begin(), rookPositions.end(), rng);

    // convert them to sampling locations
    values.resize(numValues);
    for (size_t i = 0; i < numValues; ++i)
    {
        values[i][0] = float(rookPositions[i]) / float(numValues - 1);
        values[i][1] = float(i) / float(numValues - 1);
    }
}
