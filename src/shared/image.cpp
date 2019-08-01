/*
FILE: image.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019

Description:
A thin wrapper to some pixels, and a way to save them to disk as an image
*/

#define _CRT_SECURE_NO_WARNINGS // for stb

#include "image.h"
#include "color_spaces.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

void SaveImage(const Image& image, const char* fileName)
{
    std::vector<PixelRGBAU8> rgbaU8;

    rgbaU8.resize(image.m_pixels.size());

    PixelRGBAU8* destPixel = rgbaU8.data();
    const PixelRGBAF32_PMA* srcPixel = image.m_pixels.data();
    for (size_t pixelIndex = 0, pixelCount = image.m_width*image.m_height; pixelIndex < pixelCount; ++pixelIndex, ++destPixel, ++srcPixel)
        *destPixel = PixelRGBAU8(*srcPixel);

    stbi_write_png(fileName, image.m_width, image.m_height, 4, rgbaU8.data(), image.m_width * sizeof(rgbaU8[0]));
}

void BlendInImage(Image& image, const Image& otherImage, int pastex, int pastey)
{
    int startX = Clamp(pastex, 0, image.m_width);
    int startY = Clamp(pastey, 0, image.m_height);

    int endX = Clamp(pastex + otherImage.m_width, 0, image.m_width);
    int endY = Clamp(pastey + otherImage.m_height, 0, image.m_height);

    for (int y = startY; y < endY; ++y)
    {
        // calculate starting pixel on image we are pasting in
        int srcX = startX - pastex;
        int srcY = y - pastey;
        const PixelRGBAF32_PMA* srcPixel = &otherImage.m_pixels[srcY * otherImage.m_width + srcX];

        // calculate starting pixel on image we are pasting to
        PixelRGBAF32_PMA* destPixel = &image.m_pixels[y * image.m_width + startX];

        // do a row of pasting
        for (int x = startX; x < endX; ++x, ++srcPixel, ++destPixel)
            destPixel->BlendIn(*srcPixel);
    }
}

void BlendInImage_Resize(Image& image, const Image& otherImage, unsigned int pastex, unsigned int pastey, PixelRGBAF32 clearColor)
{
    // make a new image large enough to hold both images, and fill it with the clear color
    int width = std::max(image.m_width, int(pastex) + otherImage.m_width);
    int height = std::max(image.m_height, int(pastey) + otherImage.m_height);
    Image newImage(width, height, clearColor);

    // blend in the first image
    BlendInImage(newImage, image, 0, 0);

    // blend in the second image
    BlendInImage(newImage, otherImage, pastex, pastey);

    // set the image to the new image
    image = newImage;
}

void ResizeImageBicubic(Image& image, int newWidth, int newHeight)
{
    // scale up or down by 2x at most, repeatedly, til done
    while (image.m_width != newWidth && image.m_height != newHeight)
    {
        float scaleX = float(newWidth) / float(image.m_width);
        float scaleY = float(newHeight) / float(image.m_height);
        scaleX = Clamp(scaleX, 0.5f, 2.0f);
        scaleY = Clamp(scaleY, 0.5f, 2.0f);

        int scaledW = int(scaleX*float(image.m_width));
        int scaledH = int(scaleY*float(image.m_height));

        Image newImage(scaledW, scaledH);

        for (int y = 0; y < newImage.m_height; ++y)
        {
            PixelRGBAF32_PMA* pixel = &newImage.m_pixels[y * newImage.m_width];
            Vec2 uv;
            uv[1] = (float(y) + 0.5f) / float(newImage.m_height);
            for (int x = 0; x < newImage.m_width; ++x, ++pixel)
            {
                uv[0] = (float(x) + 0.5f) / float(newImage.m_width);
                *pixel = SampleImageBicubic(image, uv);
            }
        }

        image = newImage;
    }
}

PixelRGBAF32_PMA SampleImageBicubic(Image& image, Vec2 uv)
{
    // calculate pixel coordinates
    float x = (uv[0] * image.m_width) - 0.5f;
    int xint = int(x);
    float xfract = x - floor(x);

    float y = (uv[1] * image.m_height) - 0.5f;
    int yint = int(y);
    float yfract = y - floor(y);

    // gather 1st row
    Vec4 p00 = image.GetPixelClamped(xint - 1, yint - 1).ToVec4();
    Vec4 p10 = image.GetPixelClamped(xint + 0, yint - 1).ToVec4();
    Vec4 p20 = image.GetPixelClamped(xint + 1, yint - 1).ToVec4();
    Vec4 p30 = image.GetPixelClamped(xint + 2, yint - 1).ToVec4();

    // gather 2nd row
    Vec4 p01 = image.GetPixelClamped(xint - 1, yint + 0).ToVec4();
    Vec4 p11 = image.GetPixelClamped(xint + 0, yint + 0).ToVec4();
    Vec4 p21 = image.GetPixelClamped(xint + 1, yint + 0).ToVec4();
    Vec4 p31 = image.GetPixelClamped(xint + 2, yint + 0).ToVec4();

    // gather 3rd row
    Vec4 p02 = image.GetPixelClamped(xint - 1, yint + 1).ToVec4();
    Vec4 p12 = image.GetPixelClamped(xint + 0, yint + 1).ToVec4();
    Vec4 p22 = image.GetPixelClamped(xint + 1, yint + 1).ToVec4();
    Vec4 p32 = image.GetPixelClamped(xint + 2, yint + 1).ToVec4();

    // gather 4th row
    Vec4 p03 = image.GetPixelClamped(xint - 1, yint + 2).ToVec4();
    Vec4 p13 = image.GetPixelClamped(xint + 0, yint + 2).ToVec4();
    Vec4 p23 = image.GetPixelClamped(xint + 1, yint + 2).ToVec4();
    Vec4 p33 = image.GetPixelClamped(xint + 2, yint + 2).ToVec4();

    // interpolate each row to get 4 column values
    Vec4 col0 = CubicHermite(p00, p10, p20, p30, xfract);
    Vec4 col1 = CubicHermite(p01, p11, p21, p31, xfract);
    Vec4 col2 = CubicHermite(p02, p12, p22, p32, xfract);
    Vec4 col3 = CubicHermite(p03, p13, p23, p33, xfract);

    // interpolate the column values to get the final result
    PixelRGBAF32_PMA ret;
    ret.FromVec4(CubicHermite(col0, col1, col2, col3, yfract));
    return ret;
}