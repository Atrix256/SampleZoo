/*
FILE: image.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019

Description:
A thin wrapper to some pixels, and a way to save them to disk as an image
*/

#define _CRT_SECURE_NO_WARNINGS // for stb

#include "image.h"
#include "color_spaces.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

void SaveImage(const Image& image, const char* fileName)
{
    std::vector<PixelRGBAU8> rgbaU8;

    rgbaU8.resize(image.m_pixels.size());

    PixelRGBAU8* destPixel = rgbaU8.data();
    const PixelRGBAF32_PMA* srcPixel = image.m_pixels.data();
    for (size_t pixelIndex = 0, pixelCount = image.m_width*image.m_height; pixelIndex < pixelCount; ++pixelIndex, ++destPixel, ++srcPixel)
        *destPixel = PixelRGBAU8(*srcPixel);

    stbi_write_png(fileName, image.m_width, image.m_height, 4, rgbaU8.data(), image.m_width * sizeof(rgbaU8[0]));
}



