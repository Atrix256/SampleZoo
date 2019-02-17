/*
FILE: drawtext.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/16/2019
*/

#pragma once

#include "image.h"

Image MakeTextImage(const char* string, PixelRGBAF32 color, float textHeight);