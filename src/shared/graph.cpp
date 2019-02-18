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

void MakeGraph(const char* fileName, const std::vector<GraphItem>& graphItems, int width, float padx0, float pady0, float padx1, float pady1)
{
    // make the actual line graph itself as a seperate image that we'll paste into the larger image
    Image graphImage;
    int graphWidth = int(float(width)*0.9f);
    int graphPad = width - graphWidth;
    Vec2 dataMin = { FLT_MAX, FLT_MAX };
    Vec2 dataMax = { -FLT_MAX, -FLT_MAX };
    Vec2 dataMinUnpadded = { FLT_MAX, FLT_MAX };
    Vec2 dataMaxUnpadded = { -FLT_MAX, -FLT_MAX };
    {
        // get data range
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

        // store off unpadded data extrema so we can use it for data marks
        dataMinUnpadded = dataMin;
        dataMaxUnpadded = dataMax;

        // pad the data range by the amount specified on each axis
        float padX0 = (dataMax[0] - dataMin[0]) * padx0;
        float padY0 = (dataMax[1] - dataMin[1]) * pady0;
        float padX1 = (dataMax[0] - dataMin[0]) * padx1;
        float padY1 = (dataMax[1] - dataMin[1]) * pady1;
        dataMin[0] -= padX0;
        dataMin[1] -= padY0;
        dataMax[0] += padX1;
        dataMax[1] += padY1;

        // flip the graph over to make y=0 be at the bottom of the image
        std::swap(dataMin[1], dataMax[1]);
        std::swap(dataMinUnpadded[1], dataMaxUnpadded[1]);

        // draw the lines
        graphImage.Resize(graphWidth, graphWidth, { 0.85f, 0.85f, 0.85f, 1.0f });
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
            for (const Vec2& dataPoint : graphItem.data)
            {
                Vec2 normalized;
                normalized[0] = (dataPoint[0] - dataMin[0]) / (dataMax[0] - dataMin[0]);
                normalized[1] = (dataPoint[1] - dataMin[1]) / (dataMax[1] - dataMin[1]);

                if (!firstPoint)
                    DrawLine(graphImage, lastPoint[0], lastPoint[1], normalized[0], normalized[1], lineColor, 1.0f / 512.0f);
                firstPoint = false;
                lastPoint = normalized;
            }
        }
    }

    // TODO: axis labels and legend etc

    // TODO: make a function to draw text onto an image. do it like the below, but use the text baseline, and also take an enum for left, right or center justify
    //Image label = MakeTextImage(fileName, {0.0f, 0.0f, 0.0f, 1.0f}, 20);
    //BlendInImage(image, label, 0, 0);

    // paste the line graph into this image
    Image image(width, width, { 1.0f, 1.0f, 0.0f, 1.0f });
    BlendInImage(image, graphImage, graphPad, 0);

    // TODO: try going back to non Px version. better for line width!

    // draw axis lines
    DrawLinePx(image, graphPad-2, 0, graphPad-2, width - graphPad, { 0.0f, 0.0f, 0.0f, 1.0f }, 2.0);
    DrawLinePx(image, graphPad, width - graphPad+1, width, width - graphPad+1, { 0.0f, 0.0f, 0.0f, 1.0f }, 2.0);

    // put a mark at the minimum and maximum error and label them
    float graphPadF = float(graphPad) / float(width);
    float miny = ((dataMinUnpadded[1] - dataMin[1]) / (dataMax[1] - dataMin[1])) * 0.9f;
    float maxy = ((dataMaxUnpadded[1] - dataMin[1]) / (dataMax[1] - dataMin[1])) * 0.9f;
    DrawLine(image, graphPadF - 0.01f, maxy, graphPadF + 0.01f, maxy, { 0.0f, 0.0f, 0.0f, 1.0f }, 2.0f / 512.0f);
    DrawLine(image, graphPadF - 0.01f, miny, graphPadF + 0.01f, miny, { 0.0f, 0.0f, 0.0f, 1.0f }, 2.0f / 512.0f);
    char buffer[256];
    sprintf(buffer, "%0.2f", dataMinUnpadded[1]);
    Image label = MakeTextImage(buffer, { 0.0f, 0.0f, 0.0f, 1.0f }, 20);
    BlendInImage(image, label, graphPad, int(miny * float(width)));
    sprintf(buffer, "%0.2f", dataMaxUnpadded[1]);
    label = MakeTextImage(buffer, { 0.0f, 0.0f, 0.0f, 1.0f }, 20);
    BlendInImage(image, label, graphPad, int(maxy * float(width)));

    // TODO: should BlendInImage take floats? maybe call it Px instead?

    // save the final image
    SaveImage(image, fileName);
}