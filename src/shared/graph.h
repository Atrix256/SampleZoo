/*
FILE: graph.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/17/2019
*/

#pragma once

#include <vector>
#include <string>
#include <array>
#include "vector.h"

struct GraphItem
{
    std::string label;
    std::vector<Vec2> data;
};

struct AxisTick
{
    std::string label;
    float value;
};

void MakeGraph(const char* fileName, const std::vector<GraphItem>& graphItems, const std::vector<float> xAxisTicks, int width, bool loglog);
