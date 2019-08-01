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
    Image()
    {
        m_width = 0;
        m_height = 0;
    }

    Image(int width, int height, PixelRGBAF32 clearColor = PixelRGBAF32(1.0f, 1.0f, 1.0f, 1.0f))
    {
        Resize(width, height, clearColor);
    }

    void Resize(int width, int height, PixelRGBAF32 clearColor = PixelRGBAF32(1.0f, 1.0f, 1.0f, 1.0f))
    {
        m_width = width;
        m_height = height;
        m_pixels.resize(m_width*m_height);
        std::fill(m_pixels.begin(), m_pixels.end(), PixelRGBAF32_PMA(clearColor));
    }

    PixelRGBAF32_PMA GetPixelClamped(int x, int y)
    {
        x = Clamp(x, 0, m_width - 1);
        y = Clamp(y, 0, m_height - 1);

        return m_pixels[y * m_width + x];
    }

    int m_width;
    int m_height;
    std::vector<PixelRGBAF32_PMA> m_pixels;
};

void SaveImage(const Image& image, const char* fileName);

void BlendInImage(Image& image, const Image& otherImage, int pastex, int pastey);

void BlendInImage_Resize(Image& image, const Image& otherImage, unsigned int pastex, unsigned int pastey, PixelRGBAF32 clearColor);

void ResizeImageBicubic(Image& image, int newWidth, int newHeight);

PixelRGBAF32_PMA SampleImageBicubic(Image& image, Vec2 uv);
