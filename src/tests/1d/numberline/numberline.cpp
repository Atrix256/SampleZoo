/*
FILE: numberline.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019

Description:
Makes a numberline image and saves it to disk
*/

#include "numberline.h"
#include "stb/stb_image_write.h"
#include "shared/pixel.h"
#include "shared/drawing.h"
#include "shared/image.h"

void Tests::_1d::Numberline::MakeNumberline(const char* pngFileName, const std::vector<float>& samples, size_t width_)
{
    const int width = int(width_);
    const int height = int(float(width) * 0.25f);

    Image image(width, height, { 224, 224, 224 });

    int numberLineXBegin = int(float(width) * 0.1f);
    int numberLineXEnd = int(float(width) * 0.9f);

    int numberLineYBegin = int(float(height) * 0.3f);
    int numberLineYEnd = int(float(height) * 0.7f);

    int numberLineYSampleBegin = int(float(height) * 0.4f);
    int numberLineYSampleEnd = int(float(height) * 0.6f);

    int imageYMiddle = height / 2;

    DrawLine(image, numberLineXBegin, imageYMiddle, numberLineXEnd, imageYMiddle, { 32,32,32 });
    DrawLine(image, numberLineXBegin, numberLineYBegin, numberLineXBegin, numberLineYEnd, { 32, 32, 32 });
    DrawLine(image, numberLineXEnd, numberLineYBegin, numberLineXEnd, numberLineYEnd, { 32, 32, 32 });

    for (float f : samples)
    {
        int sampleX = int(float(f) * (numberLineXEnd - numberLineXBegin) + numberLineXBegin);
        DrawLine(image, sampleX, numberLineYSampleBegin, sampleX, numberLineYSampleEnd, {32, 32, 255});
    }

    stbi_write_png(pngFileName, width, height, 3, image.m_pixels.data(), width * sizeof(image.m_pixels[0]));
}