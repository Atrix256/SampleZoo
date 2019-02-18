/*
FILE: graph.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/17/2019
*/

#include "graph.h"
#include "image.h"
#include "drawtext.h"
#include "drawing.h"
#include "color_spaces.h"

static const float c_goldenRatioConjugate = 0.61803398875f;

// TODO: make y axis ticks get passed in too?

void MakeGraph(const char* fileName, const std::vector<GraphItem>& graphItems, const std::vector<float> xAxisTicks, int width, bool loglog)
{
    static const Vec2 graphMin = { 0.1f, 0.0f };
    static const Vec2 graphMax = { 1.0f, 0.9f };

    static const float virtualPixel = 1.0f / 512.0f;

    static const float log10epsilon = 0.0001f;

    // make the graph image
    Image image(width, width, { 1.0f, 1.0f, 1.0f, 1.0f });

    // draw a darker region where the line graph will be
    DrawBox(image, graphMin, graphMax, { 0.85f, 0.85f, 0.85f, 1.0f });

    // draw the axis lines
    DrawLine(image, graphMin[0] - virtualPixel * 2.0f, graphMin[1]                      , graphMin[0] - virtualPixel * 2.0f, graphMax[1] + virtualPixel * 2.0f, { 0.0f, 0.0f, 0.0f, 1.0f }, 3.0 * virtualPixel);
    DrawLine(image, graphMin[0] - virtualPixel * 2.0f, graphMax[1] + virtualPixel * 2.0f, graphMax[0]                      , graphMax[1] + virtualPixel * 2.0f, { 0.0f, 0.0f, 0.0f, 1.0f }, 3.0 * virtualPixel);

    // get data range
    Vec2 dataMin = { FLT_MAX, FLT_MAX };
    Vec2 dataMax = { -FLT_MAX, -FLT_MAX };
    Vec2 dataMinUnpadded = { FLT_MAX, FLT_MAX };
    Vec2 dataMaxUnpadded = { -FLT_MAX, -FLT_MAX };
    {
        for (const GraphItem& graphItem : graphItems)
        {
            for (const Vec2& dataPoint : graphItem.data)
            {
                dataMin[0] = std::min(dataMin[0], dataPoint[0]);
                dataMin[1] = std::min(dataMin[1], dataPoint[1]);

                dataMax[0] = std::max(dataMax[0], dataPoint[0]);
                dataMax[1] = std::max(dataMax[1], dataPoint[1]);
            }
        }

        dataMinUnpadded = dataMin;
        dataMaxUnpadded = dataMax;

        // pad the top and right of the graph a bit
        dataMax[0] += (dataMax[0] - dataMin[0]) * 0.25f;
        dataMax[1] += (dataMax[1] - dataMin[1]) * 0.25f;

        // flip the graph over to make y=0 be at the bottom of the image
        std::swap(dataMin[1], dataMax[1]);
        std::swap(dataMinUnpadded[1], dataMaxUnpadded[1]);

        // if they want a log/log graph
        if (loglog)
        {
            dataMin[0] = log10f(std::max(dataMin[0], log10epsilon));
            dataMin[1] = log10f(std::max(dataMin[1], log10epsilon));
            dataMax[0] = log10f(std::max(dataMax[0], log10epsilon));
            dataMax[1] = log10f(std::max(dataMax[1], log10epsilon));
        }
    }

    // define the lambda to convert from data space to image space
    auto DataToImage = [&dataMin, &dataMax, loglog] (Vec2 dataSpace) -> Vec2
    {
        // if they want a log/log graph
        if (loglog)
        {
            dataSpace[0] = log10f(std::max(dataSpace[0], log10epsilon));
            dataSpace[1] = log10f(std::max(dataSpace[1], log10epsilon));
        }

        // make the data point be in [0,1) space
        Vec2 imageSpace;
        imageSpace[0] = (dataSpace[0] - dataMin[0]) / (dataMax[0] - dataMin[0]);
        imageSpace[1] = (dataSpace[1] - dataMin[1]) / (dataMax[1] - dataMin[1]);

        // make the data point be in the [graphMin, graphMax) space
        imageSpace[0] = graphMin[0] + imageSpace[0] * (graphMax[0] - graphMin[0]);
        imageSpace[1] = graphMin[1] + imageSpace[1] * (graphMax[1] - graphMin[1]);
        return imageSpace;
    };

    // put a mark at the minimum and maximum y value and label them
    {
        char buffer[256];

        Vec2 min = DataToImage(dataMinUnpadded);
        Vec2 max = DataToImage(dataMaxUnpadded);

        DrawLine(image, min[0] - virtualPixel * 7.0f, min[1], min[0] - virtualPixel * 2.0f, min[1], { 0.0f, 0.0f, 0.0f, 1.0f }, 2.0f * virtualPixel);
        sprintf(buffer, "%0.2f", dataMinUnpadded[1]);
        DrawText(image, buffer, { 0.0f, 0.0f, 0.0f, 1.0f }, 20.0f * virtualPixel, Vec2{ min[0], min[1] } - Vec2{ virtualPixel * 10.0f, 0.0f }, TextHAlign::Right, TextVAlign::Top);

        DrawLine(image, min[0] - virtualPixel * 7.0f, max[1], min[0] - virtualPixel * 2.0f, max[1], { 0.0f, 0.0f, 0.0f, 1.0f }, 2.0f * virtualPixel);
        sprintf(buffer, "%0.2f", dataMaxUnpadded[1]);
        DrawText(image, buffer, { 0.0f, 0.0f, 0.0f, 1.0f }, 20.0f * virtualPixel, Vec2{ min[0], max[1] } - Vec2{ virtualPixel * 10.0f, 0.0f }, TextHAlign::Right, TextVAlign::Top);
    }

    // draw x axis ticks
    for (float f : xAxisTicks)
    {
        Vec2 data = { f, dataMinUnpadded[0] };
        Vec2 pos = DataToImage(data);

        DrawLine(image, pos[0], graphMax[1] + virtualPixel * 2.0f, pos[0], graphMax[1] + virtualPixel * 7.0f, { 0.0f, 0.0f, 0.0f, 1.0f }, 2.0f * virtualPixel);

        char buffer[256];
        sprintf(buffer, "%i", int(f));
        DrawText(image, buffer, { 0.0f, 0.0f, 0.0f, 1.0f }, 20.0f * virtualPixel, Vec2{ pos[0], graphMax[1] + virtualPixel * 10.0f }, TextHAlign::Right, TextVAlign::Top);
    }

    // draw the line graph in a specific region of the image
    {
        int graphItemIndex = -1;
        for (const GraphItem& graphItem : graphItems)
        {
            // Use the golden ratio to choose nearly maximally different hues for however many graph lines we have.
            // Use HSV to RGB conversion to get an RGB color out of that.
            graphItemIndex++;
            std::array<float, 3> rgb = HSVToRGB(std::fmodf(float(graphItemIndex)*c_goldenRatioConjugate, 1.0f), 0.95f, 0.95f);
            PixelRGBAF32 lineColor = { rgb[0], rgb[1], rgb[2], 1.0f };

            // draw the lines for the line graph
            bool firstPoint = true;
            Vec2 lastPoint;
            for (Vec2 dataPoint : graphItem.data)
            {
                // get the data point location on the image
                Vec2 imageSpacePoint = DataToImage(dataPoint);

                // draw the line segment
                if (!firstPoint)
                    DrawLine(image, lastPoint[0], lastPoint[1], imageSpacePoint[0], imageSpacePoint[1], lineColor, virtualPixel);
                firstPoint = false;
                lastPoint = imageSpacePoint;
            }
        }
    }

    // save the final image
    SaveImage(image, fileName);

    // TODO: legend
    // TODO: for x axis ticks (and y!) maybe have user supply text to show.
    // TODO: is log10 best? there is a lot of space from 0 to 1...
}