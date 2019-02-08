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

void DrawLine(Image& image, int x1, int y1, int x2, int y2, const PixelRGBU8& color);