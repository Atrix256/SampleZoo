/*
FILE: pixel.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019

Description:
defines the types used to represent a pixel.
*/

#pragma once

#include <stdint.h>

struct PixelRGBU8
{
    uint8_t r, g, b;
};

struct PixelRGBF32
{
    float r, g, b;
};