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

    float numberLineXBegin = 0.1f;
    float numberLineXEnd = 0.9f;

    float numberLineYBegin = 0.3f;
    float numberLineYEnd = 0.7f;

    float numberLineYSampleBegin = 0.4f;
    float numberLineYSampleEnd = 0.6f;

    DrawLine(image, numberLineXBegin, 0.5f, numberLineXEnd, 0.5f, { 32,32,32 });
    DrawLine(image, numberLineXBegin, numberLineYBegin, numberLineXBegin, numberLineYEnd, { 32, 32, 32 });
    DrawLine(image, numberLineXEnd, numberLineYBegin, numberLineXEnd, numberLineYEnd, { 32, 32, 32 });

    for (float f : samples)
    {
        float sampleX = float(f) * (numberLineXEnd - numberLineXBegin) + numberLineXBegin;
        DrawLine(image, sampleX, numberLineYSampleBegin, sampleX, numberLineYSampleEnd, {32, 192, 192 });
    }

    stbi_write_png(pngFileName, width, height, 3, image.m_pixels.data(), width * sizeof(image.m_pixels[0]));
}
