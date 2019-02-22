/*
FILE: LDS.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/11/2019

Description: Low discrepancy sequences
*/

#include "codegen.h"

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

static void VanDerCorput(std::vector<float>& values, size_t base)
{
    for (size_t i = 0; i < values.size(); ++i)
    {
        values[i] = 0.0f;
        float denominator = float(base);
        size_t n = i;
        while (n > 0)
        {
            size_t multiplier = n % base;
            values[i] += float(multiplier) / denominator;
            n = n / base;
            denominator *= base;
        }
    }
}

void Samples::_1d::LDS::Sobol(std::vector<float>& values, size_t numValues)
{
    values.resize(numValues);
    size_t sampleInt = 0;
    for (size_t i = 0; i < numValues; ++i)
    {
        size_t ruler = Ruler(i + 1);
        size_t direction = size_t(size_t(1) << size_t(31 - ruler));
        sampleInt = sampleInt ^ direction;
        values[i] = float(sampleInt) / std::pow(2.0f, 32.0f);
    }
}

void Samples::_1d::LDS::VanDerCorput2(std::vector<float>& values, size_t numValues)
{
    values.resize(numValues);
    VanDerCorput(values, 2);
}

void Samples::_1d::LDS::VanDerCorput3(std::vector<float>& values, size_t numValues)
{
    values.resize(numValues);
    VanDerCorput(values, 3);
}

void Samples::_1d::LDS::VanDerCorput5(std::vector<float>& values, size_t numValues)
{
    values.resize(numValues);
    VanDerCorput(values, 5);
}
