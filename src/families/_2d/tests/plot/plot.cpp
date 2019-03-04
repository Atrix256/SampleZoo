/*
FILE: plot.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 3/3/2019
*/

#include "codegen.h"
#include "stb/stb_image_write.h"
#include "shared/pixel.h"
#include "shared/drawing.h"
#include "shared/image.h"
#include "shared/color_spaces.h"
#include "shared/math.h"
#include "shared/drawtext.h"

static Image MakePlot(const std::vector<Vec2>& samples, int width)
{
    const int height = width;

    Image image(width, height, { 1.0f, 1.0f, 1.0f, 1.0f});

    float paddingMinX = 0.1f;
    float paddingMaxX = 0.9f;
    float paddingMinY = 0.1f;
    float paddingMaxY = 0.9f;

    DrawBox(image, Vec2{ paddingMinX, paddingMinY }, Vec2{ paddingMaxX, paddingMaxY }, { 0.85f, 0.85f, 0.85f, 1.0f });

    for (size_t i = 0; i < samples.size(); ++i)
    {
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

        Vec2 paddingMin = { paddingMinX, paddingMinY };
        Vec2 paddingMax = { paddingMaxX, paddingMaxY };

        // draw the 2d sample location
        Vec2 samplePos = samples[i] * (paddingMax - paddingMin) + paddingMin;
        DrawCircle(image, samplePos, 5.0f / 512.0f, color);

        // draw the x axis projection
        DrawCircle(image, Vec2{ 0.05f, samplePos[1] }, 5.0f / 512.0f, color);

        // draw the y axis projection
        DrawCircle(image, Vec2{ samplePos[0], 0.95f }, 5.0f / 512.0f, color);
    }

    // draw borders
    DrawLine(image, paddingMinX, paddingMinY, paddingMinX, paddingMaxY, { 0.125f, 0.125f, 0.125f, 1.0f }, 2.0f / 512.0f);
    DrawLine(image, paddingMaxX, paddingMinY, paddingMaxX, paddingMaxY, { 0.125f, 0.125f, 0.125f, 1.0f }, 2.0f / 512.0f);
    DrawLine(image, paddingMinX, paddingMinY, paddingMaxX, paddingMinY, { 0.125f, 0.125f, 0.125f, 1.0f }, 2.0f / 512.0f);
    DrawLine(image, paddingMinX, paddingMaxY, paddingMaxX, paddingMaxY, { 0.125f, 0.125f, 0.125f, 1.0f }, 2.0f / 512.0f);

    return image;
}

void _2d::Tests::Plot::MakePlot(const std::vector<std::vector<SampleGenerateInfo_2d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
    char fileName[256];
    std::vector<size_t> sampleCounts = { 8, 16, 32, 64 };

    for (const std::vector<SampleGenerateInfo_2d>& sampleType : sampleFunctions)
    {
        for (const SampleGenerateInfo_2d& sampleFunction : sampleType)
        {
            Image result;

            std::vector<Vec2> samples;
            for (size_t sampleCountIndex = 0; sampleCountIndex < sampleCounts.size(); ++sampleCountIndex)
            {
                sampleFunction.function(samples, sampleCounts[sampleCountIndex], sampleFunction.cacheKey, false);
                Image newImage = ::MakePlot(samples, 256);

                char buffer[256];
                sprintf(buffer, "%zu samples", sampleCounts[sampleCountIndex]);
                DrawText(newImage, buffer, { 0.0f, 0.0f, 0.0f, 1.0f }, 40.0f / 512.0f, Vec2{ 0.5f, 0.0f }, TextHAlign::Center, TextVAlign::Top);

                BlendInImage_Resize(result, newImage, result.m_width, 0, { 0.0f, 0.0f, 0.0f, 1.0f });
            }

            sprintf(fileName, "output/%s/samples/%s/%s_%s.png", sampleFunction.sampleFamily, sampleFunction.sampleType, testName, sampleFunction.name);
            SaveImage(result, fileName);
        }
    }
}
