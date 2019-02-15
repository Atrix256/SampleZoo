/*
FILE: numberline.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019

Description:
Makes a numberline image and saves it to disk
*/

#include "codegen.h"
#include "stb/stb_image_write.h"
#include "shared/pixel.h"
#include "shared/drawing.h"
#include "shared/image.h"
#include "shared/color_spaces.h"
#include "shared/math.h"

static void MakeNumberline(const char* fileName, const std::vector<float>& samples, int width)
{
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

    for (size_t i = 0; i < samples.size(); ++i)
    {
        float f = samples[i];
        static const float srcColor[3] = { 1, 0, 0 };
        static const float destColor[3] = { 0, 1, 0 };

        float t = float(i) / float(samples.size() - 1);
        uint8_t r = FloatToU8(LinearToSRGB(Lerp(srcColor[0], destColor[0], t)));
        uint8_t g = FloatToU8(LinearToSRGB(Lerp(srcColor[1], destColor[1], t)));
        uint8_t b = FloatToU8(LinearToSRGB(Lerp(srcColor[2], destColor[2], t)));

        float sampleX = f * (numberLineXEnd - numberLineXBegin) + numberLineXBegin;
        DrawLine(image, sampleX, numberLineYSampleBegin, sampleX, numberLineYSampleEnd, { r, g, b });
    }

    stbi_write_png(fileName, width, height, 3, image.m_pixels.data(), width * sizeof(image.m_pixels[0]));
}

void Tests::_1d::Numberline::MakeNumberline(SampleGenerateInfo_1d* sampleFunctions, size_t sampleFunctionCount, size_t* sampleCounts, size_t sampleCountCounts)
{
    char fileName[256];
    for (size_t sampleFunctionIndex = 0; sampleFunctionIndex < sampleFunctionCount; ++sampleFunctionIndex)
    {
        SampleGenerateInfo_1d& sampleFunction = sampleFunctions[sampleFunctionIndex];

        std::vector<float> samples;
        for (size_t sampleCountIndex = 0; sampleCountIndex < sampleCountCounts; ++sampleCountIndex)
        {
            size_t sampleCount = sampleCounts[sampleCountIndex];
            sampleFunction.function(samples, sampleCount);
            sprintf(fileName, "output/samples/%s/%s/%s_%zu.png", sampleFunction.sampleFamily, sampleFunction.sampleType, sampleFunction.name, sampleCount);
            ::MakeNumberline(fileName, samples, 512);
        }
    }
}
