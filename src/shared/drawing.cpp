/*
FILE: drawing.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019

Description:
Some helper functions for drawing 2d images
*/

#include "drawing.h"
#include "image.h"
#include "math.h"
#include <algorithm>

void DrawLine(Image& image, float x1_, float y1_, float x2_, float y2_, const PixelRGBAF32& color, float lineWidth_)
{
    int x1 = int(x1_ * float(image.m_width));
    int x2 = int(x2_ * float(image.m_width));
    int y1 = int(y1_ * float(image.m_height));
    int y2 = int(y2_ * float(image.m_height));

    // Convert line width to pixels by multiplying by image width. not exactly right (aspect ratio / rectangular images not handled well) but whatever.
    float lineWidth = lineWidth_ * float(image.m_width);

    const PixelRGBAF32_PMA colorPMA(color);

    // pad the AABB of pixels we scan, to account for anti aliasing
    int startX = std::max(std::min(x1, x2) - 4 - int(2 * lineWidth), 0);
    int startY = std::max(std::min(y1, y2) - 4 - int(2 * lineWidth), 0);
    int endX = std::min(std::max(x1, x2) + 4 + int(2 * lineWidth), image.m_width - 1);
    int endY = std::min(std::max(y1, y2) + 4 + int(2 * lineWidth), image.m_height - 1);

    // if (x1,y1) is A and (x2,y2) is B, get a normalized vector from A to B called AB
    float ABX = float(x2 - x1);
    float ABY = float(y2 - y1);
    float ABLen = std::sqrtf(ABX*ABX + ABY * ABY);
    ABX /= ABLen;
    ABY /= ABLen;

    // scan the AABB of our line segment, drawing pixels for the line, as is appropriate
    for (int iy = startY; iy <= endY; ++iy)
    {
        PixelRGBAF32_PMA* pixel = &image.m_pixels[(iy * image.m_width + startX)];
        for (int ix = startX; ix <= endX; ++ix)
        {
            // project this current pixel onto the line segment to get the closest point on the line segment to the point
            float ACX = float(ix - x1);
            float ACY = float(iy - y1);
            float lineSegmentT = ACX * ABX + ACY * ABY;
            lineSegmentT = std::min(lineSegmentT, ABLen);
            lineSegmentT = std::max(lineSegmentT, 0.0f);
            float closestX = float(x1) + lineSegmentT * ABX;
            float closestY = float(y1) + lineSegmentT * ABY;

            // calculate the distance from this pixel to the closest point on the line segment
            float distanceX = float(ix) - closestX;
            float distanceY = float(iy) - closestY;
            float distance = std::sqrtf(distanceX * distanceX + distanceY * distanceY);

            // account for line width
            distance -= lineWidth / 2.0f;

            // use the distance to figure out how transparent the pixel should be, and apply the color to the pixel
            float alpha = SmoothStep(distance, 0.75f, 0.0f);

            PixelRGBAF32_PMA colorPMACopy = colorPMA;
            colorPMACopy.MultiplyAlpha(alpha);

            pixel->BlendIn(colorPMACopy);

            pixel++;
        }
    }
}