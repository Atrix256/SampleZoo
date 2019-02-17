/*
FILE: graph.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/17/2019
*/

#include "graph.h"
#include "image.h"
#include "drawtext.h"

void MakeGraph(const char* fileName, const std::vector<GraphItem>& graphItems, int width)
{
    Image image(width, width, { 0.85f, 0.85f, 0.85f, 1.0f });

    Vec2 dataMin = { FLT_MAX, FLT_MAX };
    Vec2 dataMax = { -FLT_MAX, -FLT_MAX };

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

    // TODO: could draw the graph to a square, then paste that square into a larger image with labels etc.

    Image label = MakeTextImage(fileName, {0.0f, 0.0f, 0.0f, 1.0f}, 20);

    BlendInImage(image, label, 0, 0);

    SaveImage(image, fileName);
}