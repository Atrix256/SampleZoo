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

float MakeCharImage(Image& image, int c, PixelRGBAF32 color, float scale, float x_shift, int &yoffset)
{
    int advanceWidth;
    int leftSideBearing;
    stbtt_GetCodepointHMetrics(&c_fontInfo, c, &advanceWidth, &leftSideBearing);

    int x0, y0, x1, y1;
    stbtt_GetCodepointBitmapBoxSubpixel(&c_fontInfo, c, scale, scale, x_shift, 0, &x0, &y0, &x1, &y1);
    yoffset = y0;

    int bitmapWidth, bitmapHeight;
    unsigned char *bitmap = stbtt_GetCodepointBitmapSubpixel(&c_fontInfo, 0.0f,  scale, x_shift, 0.0f, c, &bitmapWidth, &bitmapHeight, nullptr, nullptr);

    image.Resize(bitmapWidth, bitmapHeight, {0.0f, 0.0f, 0.0f, 0.0f});

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

    return float(advanceWidth)*scale;
}

Image MakeTextImage(const char* string, PixelRGBAF32 color, float textHeight, int& baseline)
{
    EnsureFontLoaded();

    Image stringImage;

    float scale = stbtt_ScaleForPixelHeight(&c_fontInfo, textHeight);
    int ascent;
    int descent;
    stbtt_GetFontVMetrics(&c_fontInfo, &ascent, &descent, 0);
    baseline = (int)(float(ascent)*scale);
    float xpos = 0.0f;

    const char *c = string;
    while (*c)
    {
        Image charImage;
        float x_shift = xpos - (float)floor(xpos);
        int yOffset;
        float advance = MakeCharImage(charImage, *c, color, scale, x_shift, yOffset);

        BlendInImage_Resize(stringImage, charImage, unsigned int(xpos), baseline + yOffset, { 0.0f, 0.0f, 0.0f, 0.0f });

        if (c[1])
            xpos += scale * float(stbtt_GetCodepointKernAdvance(&c_fontInfo, c[0], c[1]));

        xpos += advance;
        c++;
    }

    return stringImage;
}

void DrawTextPx(Image& image, const char* string, PixelRGBAF32 color, float textHeight, int posx, int posy, TextAlign align)
{
    int baseline;
    Image text = MakeTextImage(string, color, textHeight, baseline);

    int x = posx;
    int y = posy - text.m_height / 2 - (text.m_height - baseline);

    switch (align)
    {
        case TextAlign::Left:
        {
            break;
        }
        case TextAlign::Right:
        {
            x -= text.m_width;
            break;
        }
        case TextAlign::Center:
        {
            x -= text.m_width / 2;
            break;
        }
    }

    BlendInImage(image, text, x, y);
}
