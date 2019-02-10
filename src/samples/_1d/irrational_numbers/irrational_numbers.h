/*
FILE: irrational_numbers.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019
*/

#pragma once

#include <vector>

namespace Samples
{
    namespace _1d
    {
        namespace IrrationalNumbers
        {
            void GoldenRatio(std::vector<float>& values, size_t numValues);
            void Pi(std::vector<float>& values, size_t numValues);
            void Sqrt2(std::vector<float>& values, size_t numValues);

            template <int N, int D>
            void Rational(std::vector<float>& values, size_t numValues)
            {
                _Rational(values, numValues, N, D);
            }
            void _Rational(std::vector<float>& values, size_t numValues, int numerator, int denominator);
        };
    };
};
