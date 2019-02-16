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

void MakeCharPMA(Image& image, int c, PixelRGBAF32 color, float scaleX, float scaleY)
{
    EnsureFontLoaded();

    const PixelRGBAF32_PMA colorPMA(color);

    int width, height;
    unsigned char *bitmap = stbtt_GetCodepointBitmap(&c_fontInfo, scaleX, stbtt_ScaleForPixelHeight(&c_fontInfo, scaleY), c, &width, &height, nullptr, nullptr);

    image.Resize(width, height, {0.0f, 0.0f, 0.0f, 1.0f});

    const unsigned char* srcPixel = bitmap;
    PixelRGBAF32_PMA* destPixel = image.m_pixels.data();
    for (int pixelIndex = 0, pixelCount = width * height; pixelIndex < pixelCount; ++pixelIndex, ++destPixel, ++srcPixel)
    {
        PixelRGBAF32_PMA colorPMACopy(colorPMA);
        float alpha = float(*srcPixel) / 255.0f;
        colorPMACopy.MultiplyAlpha(alpha);
        destPixel->BlendIn(colorPMACopy);
    }

    stbtt_FreeBitmap(bitmap, nullptr);
}

void MakeTextPMA(const char* string)
{
    Image image;
    MakeCharPMA(image, 'Q', { 1.0f, 1.0f, 0.0f, 1.0f }, 0.0f, 22.0f);
    SaveImage(image, "Q.png");

    // TODO: make the MakeCharBitmap() function, and make one for a string passed in

    /*
    int w, h, i, j, c, s;
    c = 'a';
    s = ' ';
    
    for (int iz = 0; iz < strlen(string); ++iz)
    {
        c = string[iz];
        unsigned char *bitmap = stbtt_GetCodepointBitmap(&c_fontInfo, 0.0f, stbtt_ScaleForPixelHeight(&c_fontInfo, s), c, &w, &h, 0, 0);

        for (j = 0; j < h; ++j) {
            for (i = 0; i < w; ++i)
                putchar(" .:ioVM@"[bitmap[j*w + i] >> 5]);
            putchar('\n');
        }

        stbtt_FreeBitmap(bitmap, nullptr);
    }

    // TODO: i think you need to free memory with stbtt_FreeBitmap
    */
}

void TextTest(void)
{
    MakeTextPMA("Hi Chanel");
}
