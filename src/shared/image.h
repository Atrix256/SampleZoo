/*
FILE: image.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019

Description:
A thin wrapper to some pixels, and a way to save them to disk as an image
*/

#pragma once

#include "pixel.h"
#include <vector>

// Images are RGBAF32, and are stored as premultiplied alpha

struct Image
{
    Image(int width, int height, PixelRGBAF32 clearColor = PixelRGBAF32( 1.0f, 1.0f, 1.0f, 1.0f ))
    {
        m_width = width;
        m_height = height;
        m_pixels.resize(m_width*m_height);
        std::fill(m_pixels.begin(), m_pixels.end(), PixelRGBAF32_PMA(clearColor));
    }

    int m_width;
    int m_height;
    std::vector<PixelRGBAF32_PMA> m_pixels;
};

void SaveImage(const Image& image, const char* fileName);