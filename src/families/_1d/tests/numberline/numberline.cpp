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
#include "shared/drawtext.h"

static Image MakeNumberline(const std::vector<float>& samples, int width)
{
    const int height = int(float(width) * 0.125f);

    Image image(width, height, { 0.85f, 0.85f, 0.85f, 1.0f});

    float numberLineXBegin = 0.025f;
    float numberLineXEnd = 0.975f;

    float numberLineYBegin = 0.2f;
    float numberLineYEnd = 0.8f;

    float numberLineYSampleBegin = 0.3f;
    float numberLineYSampleEnd = 0.7f;

    DrawLine(image, numberLineXBegin, 0.5f, numberLineXEnd, 0.5f, { 0.125f, 0.125f, 0.125f, 1.0f }, 2.0f / 512.0f);
    DrawLine(image, numberLineXBegin, numberLineYBegin, numberLineXBegin, numberLineYEnd, { 0.125f, 0.125f, 0.125f, 1.0f}, 2.0f / 512.0f);
    DrawLine(image, numberLineXEnd, numberLineYBegin, numberLineXEnd, numberLineYEnd, { 0.125f, 0.125f, 0.125f, 1.0f }, 2.0f / 512.0f);

    for (size_t i = 0; i < samples.size(); ++i)
    {
        float f = samples[i];
        static const PixelRGBAF32 srcColor(1.0f, 0.0f, 0.0f, 1.0f);
        static const PixelRGBAF32 destColor(0.0f, 1.0f, 0.0f, 1.0f);

        float t = float(i) / float(samples.size() - 1);
        PixelRGBAF32 color;
        color.r = Lerp(srcColor.r, destColor.r, t);
        color.g = Lerp(srcColor.g, destColor.g, t);
        color.b = Lerp(srcColor.b, destColor.b, t);
        color.a = Lerp(srcColor.a, destColor.a, t);

        // normalize the interpolated color to make the middle yellow part brighter
        float len = sqrtf(color.r*color.r + color.g*color.g + color.b*color.b);
        color.r /= len;
        color.g /= len;
        color.b /= len;

        float sampleX = f * (numberLineXEnd - numberLineXBegin) + numberLineXBegin;
        DrawLine(image, sampleX, numberLineYSampleBegin, sampleX, numberLineYSampleEnd, color, 1.0f / 512.0f);
    }

    return image;
}

void _1d::Tests::Numberline::MakeNumberline(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName)
{
    char fileName[256];
    std::vector<size_t> sampleCounts = { 8, 16, 32, 64 };

    for (const std::vector<SampleGenerateInfo_1d>& sampleType : sampleFunctions)
    {
        for (const SampleGenerateInfo_1d& sampleFunction : sampleType)
        {
            Image numberlines;

            std::vector<float> samples;
            for (size_t sampleCountIndex = 0; sampleCountIndex < sampleCounts.size(); ++sampleCountIndex)
            {
                sampleFunction.function(samples, sampleCounts[sampleCountIndex], false);
                Image newImage = ::MakeNumberline(samples, 512);

                BlendInImage_Resize(numberlines, newImage, 0, numberlines.m_height, { 0.0f, 0.0f, 0.0f, 1.0f });
            }

            Image result(numberlines.m_width + 128, numberlines.m_height, { 1.0f, 1.0f, 1.0f, 1.0f });
            BlendInImage(result, numberlines, 128, 0);

            for (size_t i = 0; i < sampleCounts.size(); ++i)
            {
                float posY = float(i) / float(sampleCounts.size()) + 1.0f / float(sampleCounts.size() * 2);
                char buffer[256];
                sprintf(buffer, "%zu samples", sampleCounts[i]);

                Vec2 pos;
                pos[0] = 64.0f / (512.0f + 128.0f);
                pos[1] = posY;

                DrawText(result, buffer, { 0.0f, 0.0f, 0.0f, 1.0f }, 40.0f / 512.0f, pos, TextHAlign::Center, TextVAlign::Center);
            }

            sprintf(fileName, "output/%s/samples/%s/%s_%s.png", sampleFunction.sampleFamily, sampleFunction.sampleType, testName, sampleFunction.name);
            SaveImage(result, fileName);
        }
    }
}
