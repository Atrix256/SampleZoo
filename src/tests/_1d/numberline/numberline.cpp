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
#include "shared/color_spaces.h"
#include "shared/math.h"

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

    for(size_t i = 0; i < samples.size(); ++i)
    {
        float f = samples[i];
        static const uint8_t srcColor[3] = { 255,0,0 };
        static const uint8_t destColor[3] = { 0, 255, 0};

        float t = float(i) / float(samples.size() - 1);
        uint8_t r = Lerp(srcColor[0], destColor[0], t);
        uint8_t g = Lerp(srcColor[1], destColor[1], t);
        uint8_t b = Lerp(srcColor[2], destColor[2], t);

        float sampleX = f * (numberLineXEnd - numberLineXBegin) + numberLineXBegin;
        DrawLine(image, sampleX, numberLineYSampleBegin, sampleX, numberLineYSampleEnd, {r, g, b });
    }

    stbi_write_png(pngFileName, width, height, 3, image.m_pixels.data(), width * sizeof(image.m_pixels[0]));
}
