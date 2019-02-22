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

enum class GraphType
{
    Lines,
    Points
};

struct GraphDesc
{
    GraphType graphType = GraphType::Lines;
    const char* fileName = nullptr;
    const char* title = nullptr;
    const char* footer = nullptr;
    std::vector<GraphItem> graphItems;
    std::vector<GraphAxisTick> xAxisTicks;
    std::vector<GraphAxisTick> yAxisTicks;
    int width = 512;
    bool loglog = false;
    Vec2 minPad = Vec2{ 0.0f, 0.0f };
    Vec2 maxPad = Vec2{ 0.0f, 0.0f };
};

void MakeGraph(const GraphDesc& desc);
