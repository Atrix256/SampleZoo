/*
FILE: LDS.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 3/4/2019
*/

#include "codegen.h"

static size_t ReverseBits(size_t number, size_t numBits)
{
    size_t ret = 0;
    for (size_t bitIndex = 0; bitIndex < numBits; ++bitIndex)
    {
        ret = ret << 1;
        if (number & 1)
            ret |= 1;
        number = number >> 1;
    }
    return ret;
}

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
            size_t n = ReverseBits(i, numBits) >> truncateBits;
            float base = 1.0f / 2.0f;
            while (n)
            {
                if (n & 1)
                    values[i][1] += base;
                n /= 2;
                base /= 2.0f;
            }
        }
    }
}

static void VanDerCorput(std::vector<Vec2>& values, size_t base, int axis, bool skipZero)
{
    for (size_t i = 0; i < values.size(); ++i)
    {
        values[i][axis] = 0.0f;
        float denominator = float(base);
        size_t n = i + (skipZero ? 1 : 0);
        while (n > 0)
        {
            size_t multiplier = n % base;
            values[i][axis] += float(multiplier) / denominator;
            n = n / base;
            denominator *= base;
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
    V.resize((size_t)ceil(log((double)numValues+1) / log(2.0)));  //+1 because we are skipping index 0
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
    values.resize(numValues);
    VanDerCorput(values, 2, 0, false);
    VanDerCorput(values, 3, 1, false);
}

void _2d::Samples::LDS::Halton_2_3(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    values.resize(numValues);
    VanDerCorput(values, 2, 0, true);
    VanDerCorput(values, 3, 1, true);
}

void _2d::Samples::LDS::Halton_5_7(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    values.resize(numValues);
    VanDerCorput(values, 5, 0, true);
    VanDerCorput(values, 7, 1, true);
}

void _2d::Samples::LDS::Halton_13_9(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    values.resize(numValues);
    VanDerCorput(values, 13, 0, true);
    VanDerCorput(values, 9, 1, true);
}

/*
void _2d::Samples::LDS::HammersleyWolfram2(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    ::Hammersley(values, numValues, 0);
}

void _2d::Samples::LDS::HammersleyWolfram_1Bit(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    ::Hammersley(values, numValues, 1);
}

void _2d::Samples::LDS::HammersleyWolfram_2Bits(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    ::Hammersley(values, numValues, 2);
}
*/

void _2d::Samples::LDS::HammersleyWikipedia2(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    values.resize(numValues);
    VanDerCorput(values, 2, 0, true);
    for (size_t i = 0; i < numValues; ++i)
        values[i][1] = float(i) / float(numValues);
}

void _2d::Samples::LDS::HammersleyWikipedia2Offset(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    values.resize(numValues);
    VanDerCorput(values, 2, 0, true);
    float offset = 1.0f / float(numValues * 2);
    for (size_t i = 0; i < numValues; ++i)
        values[i][1] = offset + float(i) / float(numValues);
}

void _2d::Samples::LDS::NRooks(std::vector<Vec2>& values, size_t numValues, std::mt19937& rng)
{
    // make N rooks that can't see each other on x or y axis
    std::vector<size_t> rookPositions(numValues, 0);
    for (size_t i = 0; i < numValues; ++i)
        rookPositions[i] = i;
    std::shuffle(rookPositions.begin(), rookPositions.end(), rng);

    float offset = 1.0f / float(numValues * 2);

    // convert them to sampling locations
    values.resize(numValues);
    for (size_t i = 0; i < numValues; ++i)
    {
        values[i][0] = offset + float(rookPositions[i]) / float(numValues);
        values[i][1] = offset + float(i) / float(numValues);
    }
}
