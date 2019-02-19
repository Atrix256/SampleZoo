/*
FILE: graph.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/17/2019
*/

#pragma once

#include <vector>
#include <string>
#include "vector.h"
#include "drawtext.h"

struct GraphItem
{
    std::string label;
    std::vector<Vec2> data;
};

struct GraphAxisTick
{
    float value;
    std::string label;
    TextHAlign halign;
    TextVAlign valign;
};

void MakeGraph(
    const char* fileName,
    const std::vector<GraphItem>& graphItems,
    const std::vector<GraphAxisTick> xAxisTicks,
    const std::vector<GraphAxisTick> yAxisTicks,
    int width,
    bool loglog,
    const Vec2& minPad,
    const Vec2& maxPad
);
