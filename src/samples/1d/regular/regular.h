/*
FILE: regular.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019
*/

#include <vector>

namespace Samples
{
    namespace _1d
    {
        namespace Regular
        {
            void Generate(std::vector<float>& values, size_t numValues);
            void GenerateCentered(std::vector<float>& values, size_t numValues);
            void GenerateCenteredOffset(std::vector<float>& values, size_t numValues);
        };
    };
};
