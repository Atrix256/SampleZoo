/*
FILE: drawtext.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/16/2019
*/

#define _CRT_SECURE_NO_WARNINGS // for stb

#include "drawtext.h"
#include "image.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb/stb_truetype.h"

#include <vector>
#include <stdio.h>

static std::vector<unsigned char> c_fontFile;
static stbtt_fontinfo c_fontInfo;

void EnsureFontLoaded()
{
    if (c_fontFile.size() > 0)
        return;

    FILE* file = fopen("fonts/OpenSans-Regular.ttf", "rb");
    fseek(file, 0, SEEK_END);
    c_fontFile.resize(ftell(file));
    fseek(file, 0, SEEK_SET);
    fread(c_fontFile.data(), 1, c_fontFile.size(), file);
    fclose(file);

    stbtt_InitFont(&c_fontInfo, c_fontFile.data(), stbtt_GetFontOffsetForIndex(c_fontFile.data(), 0));
}

void MakeCharImage(Image& image, int c, PixelRGBAF32 color, float textHeight)
{
    float scale = stbtt_ScaleForPixelHeight(&c_fontInfo, textHeight);
    int ascent;
    stbtt_GetFontVMetrics(&c_fontInfo, &ascent, 0, 0);
    int baseline = (int)(float(ascent)*scale);
    float xpos = 2.0f;

    // TODO: continue from .h file
    // TODO: this function should only make the image. the outer function should loop / advance position etc.



    scale = 220.0f;
    int bitmapWidth, bitmapHeight;
    unsigned char *bitmap = stbtt_GetCodepointBitmap(&c_fontInfo, 0.0f, stbtt_ScaleForPixelHeight(&c_fontInfo, scale), c, &bitmapWidth, &bitmapHeight, nullptr, nullptr);

    image.Resize(bitmapWidth, bitmapHeight, {0.0f, 0.0f, 0.0f, 1.0f});

    const unsigned char* srcPixel = bitmap;
    PixelRGBAF32_PMA* destPixel = image.m_pixels.data();
    for (int pixelIndex = 0, pixelCount = bitmapWidth * bitmapHeight; pixelIndex < pixelCount; ++pixelIndex, ++destPixel, ++srcPixel)
    {
        PixelRGBAF32_PMA colorPMA(color);
        float alpha = float(*srcPixel) / 255.0f;
        colorPMA.MultiplyAlpha(alpha);
        destPixel->BlendIn(colorPMA);
    }

    stbtt_FreeBitmap(bitmap, nullptr);
}

void MakeTextImage(const char* string, PixelRGBAF32 color, float textHeight)
{
    EnsureFontLoaded();

    Image image;
    MakeCharImage(image, 'Q', color, textHeight);
    SaveImage(image, "Q.png");

    // TODO: make the entire image final image by pasting together individual character images at the right location.

    // TODO: text image should probably be filled (cleared) with transparent black.  test that out when you use it.
}

void TextTest(void)
{
    MakeTextImage("Hi Chanel", { 1.0f, 1.0f, 0.0f, 1.0f }, 220.0f);
}
