/*
FILE: numberline.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019

Description:
Makes a numberline image and saves it to disk
*/

#pragma once

#include <vector>

namespace Tests
{
    namespace _1d
    {
        namespace Numberline
        {
            void MakeNumberline(const char* pngFileName, const std::vector<float>& samples, size_t width);
        };
    };
};