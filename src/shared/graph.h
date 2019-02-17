/*
FILE: graph.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/17/2019
*/

#pragma once

#include <vector>
#include <string>
#include <array>

typedef std::array<float, 2> Vec2;

struct GraphItem
{
    std::string label;
    std::vector<Vec2> data;
};

void MakeGraph(const char* fileName, const std::vector<GraphItem>& graphItems, int width);
