/*
FILE: discrepancy.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019

Description:
Calculates metrics about actual point densities vs expected point densitites
*/

#pragma once

#include <vector>

namespace Tests
{
    namespace _1d
    {
        namespace Discrepancy
        {
            float CalculateDiscrepancy(const std::vector<float>& samples);
            float CalculateDiscrepancyWrapAround(const std::vector<float>& samples);
        };
    };
};