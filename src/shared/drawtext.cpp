/*
FILE: drawtext.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/16/2019
*/

#define _CRT_SECURE_NO_WARNINGS // for stb

#include "drawtext.h"

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

void MakeCharBitmap()
{
    EnsureFontLoaded();
}

void TextTest(void)
{
    MakeCharBitmap();


    // TODO: make the MakeCharBitmap() function, and make one for a string passed in

    int w, h, i, j, c, s;
    c = 'a';
    s = ' ';

    const char* chanel = "chanel";

    for (int iz = 0; iz < strlen(chanel); ++iz)
    {
        c = chanel[iz];
        unsigned char *bitmap = stbtt_GetCodepointBitmap(&c_fontInfo, 0.0f, stbtt_ScaleForPixelHeight(&c_fontInfo, s), c, &w, &h, 0, 0);

        for (j = 0; j < h; ++j) {
            for (i = 0; i < w; ++i)
                putchar(" .:ioVM@"[bitmap[j*w + i] >> 5]);
            putchar('\n');
        }
    }

    // TODO: i think you need to free memory with stbtt_FreeBitmap
}