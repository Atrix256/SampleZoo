/*
FILE: pixel.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019

Description:
defines the types used to represent a pixel.
*/

#pragma once

#include <stdint.h>
#include "math.h"
#include "color_spaces.h"

struct PixelRGBAF32_PMA;

struct PixelRGBAU8
{
    PixelRGBAU8(uint8_t r_ = 0, uint8_t g_ = 0, uint8_t b_ = 0, uint8_t a_ = 255)
    {
        r = r_;
        g = g_;
        b = b_;
        a = a_;
    }
    uint8_t r, g, b, a;

    // allow explicit conversion from PMA to RGBAU8
    explicit inline PixelRGBAU8(const PixelRGBAF32_PMA& src);
};

struct PixelRGBAF32
{
    PixelRGBAF32(float r_ = 0.0f, float g_ = 0.0f, float b_ = 0.0f, float a_ = 1.0f)
    {
        r = r_;
        g = g_;
        b = b_;
        a = a_;
    }
    float r, g, b, a;

    // allow explicit conversion from PMA to non PMA
    explicit inline PixelRGBAF32(const PixelRGBAF32_PMA& src);
};

struct PixelRGBAF32_PMA
{
    PixelRGBAF32_PMA(float r_ = 0.0f, float g_ = 0.0f, float b_ = 0.0f, float a_ = 1.0f)
    {
        r = r_;
        g = g_;
        b = b_;
        a = a_;
    }

    void BlendIn(const PixelRGBAF32_PMA& color)
    {
        r = color.r + r * (1.0f - color.a);
        g = color.g + g * (1.0f - color.a);
        b = color.b + b * (1.0f - color.a);
        a = color.a + a * (1.0f - color.a);
    }

    void MultiplyAlpha(float alpha)
    {
        r *= alpha;
        g *= alpha;
        b *= alpha;
        a *= alpha;
    }

    float r, g, b, a;

    // allow explicit conversion from non PMA to PMA
    explicit inline PixelRGBAF32_PMA(const PixelRGBAF32& src);
};

inline PixelRGBAU8::PixelRGBAU8(const PixelRGBAF32_PMA& src)
{
    PixelRGBAF32 srcNonPMA(src);

    float r_ = LinearToSRGB(Clamp(srcNonPMA.r, 0.0f, 1.0f));
    float g_ = LinearToSRGB(Clamp(srcNonPMA.g, 0.0f, 1.0f));
    float b_ = LinearToSRGB(Clamp(srcNonPMA.b, 0.0f, 1.0f));
    float a_ = Clamp(srcNonPMA.a, 0.0f, 1.0f);

    r = uint8_t(r_*255.0f + 0.5f);
    g = uint8_t(g_*255.0f + 0.5f);
    b = uint8_t(b_*255.0f + 0.5f);
    a = uint8_t(a_*255.0f + 0.5f);
}

inline PixelRGBAF32_PMA::PixelRGBAF32_PMA(const PixelRGBAF32& src)
{
    r = src.r * src.a;
    g = src.g * src.a;
    b = src.b * src.a;
    a = src.a;
}

inline PixelRGBAF32::PixelRGBAF32(const PixelRGBAF32_PMA& src)
{
    r = src.r / src.a;
    g = src.g / src.a;
    b = src.b / src.a;
    a = src.a;
}