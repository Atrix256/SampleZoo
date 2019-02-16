/*
FILE: drawing.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019

Description:
Some helper functions for drawing 2d images
*/

#pragma once

#include "pixel.h"

struct Image;

void DrawLine(Image& image, float x1, float y1, float x2, float y2, const PixelRGBAF32& color, float lineWidth);
