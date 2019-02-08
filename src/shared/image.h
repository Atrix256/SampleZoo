/*
FILE: image.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019

Description:
A thing wrapper to some pixels
*/

#pragma once

#include "pixel.h"
#include <vector>

struct Image
{
    Image(int width, int height, const PixelRGBU8& clearColor = PixelRGBU8{ 255, 255, 255 })
    {
        m_width = width;
        m_height = height;
        m_pixels.resize(m_width*m_height);
        std::fill(m_pixels.begin(), m_pixels.end(), clearColor);
    }

    int m_width;
    int m_height;
    std::vector<PixelRGBU8> m_pixels;
};