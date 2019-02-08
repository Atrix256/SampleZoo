/*
FILE: regular.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019
*/

#pragma once

#include <vector>

namespace Samples
{
    namespace _1d
    {
        namespace Regular
        {
            void Regular(std::vector<float>& values, size_t numValues);
            void RegularCentered(std::vector<float>& values, size_t numValues);
            void RegularCenteredOffset(std::vector<float>& values, size_t numValues);
        };
    };
};
