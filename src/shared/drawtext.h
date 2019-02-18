/*
FILE: drawtext.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/16/2019
*/

#pragma once

#include "image.h"

Image MakeTextImage(const char* string, PixelRGBAF32 color, float textHeight, int& baseline);

enum class TextAlign
{
    Left,
    Right,
    Center
};

void DrawTextPx(Image& image, const char* string, PixelRGBAF32 color, float textHeight, int posx, int posy, TextAlign align);
