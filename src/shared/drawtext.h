/*
FILE: drawtext.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/16/2019
*/

#pragma once

#include "image.h"
#include "vector.h"

Image MakeTextImage(const char* string, PixelRGBAF32 color, float textHeight, int& baseline);

enum class TextAlign
{
    Left,
    Right,
    Center
};

void DrawText(Image& image, const char* string, PixelRGBAF32 color, float textHeight, Vec2& pos, TextAlign align);
