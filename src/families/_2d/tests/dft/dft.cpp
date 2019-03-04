/*
FILE: dft.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 3/3/2019
*/

#include "codegen.h"
#include "shared/image.h"
#include "shared/graph.h"
#include "shared/math.h"
#include "simple_fft/fft_settings.h"
#include "simple_fft/fft.h"
#include <vector>

struct ComplexImage2D
{
    ComplexImage2D(size_t w, size_t h)
    {
        m_width = w;
        m_height = h;
        pixels.resize(w*h, real_type(0.0f));
    }

    size_t m_width;
    size_t m_height;
    std::vector<complex_type> pixels;

    complex_type& operator()(size_t x, size_t y)
    {
        return pixels[y*m_width + x];
    }

    const complex_type& operator()(size_t x, size_t y) const
    {
        return pixels[y*m_width + x];
    }
};

void _2d::Tests::DFT::DFT(const std::vector<std::vector<SampleGenerateInfo_2d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
    static const int c_numSamples = 128;
    static const int c_sampleSourceImageWidth = 512;

    for (const std::vector<SampleGenerateInfo_2d>& sampleType : sampleFunctions)
    {
        for (const SampleGenerateInfo_2d& sampleFunction : sampleType)
        {
            // get the samples
            std::vector<Vec2> samples;
            sampleFunction.function(samples, c_numSamples, sampleFunction.cacheKey, sampleFunction.randomized);

            // make a black and white image of the samples
            ComplexImage2D sampleImageIn(c_sampleSourceImageWidth, c_sampleSourceImageWidth);
            for (const Vec2& f : samples)
            {
                size_t posX = Clamp(size_t(f[0] * float(c_sampleSourceImageWidth) + 0.5f), size_t(0), size_t(c_sampleSourceImageWidth - 1));
                size_t posY = Clamp(size_t(f[1] * float(c_sampleSourceImageWidth) + 0.5f), size_t(0), size_t(c_sampleSourceImageWidth - 1));
                sampleImageIn(posX, posY) = 1.0f;
            }

            // DFT the image to get frequency of the samples
            const char* error = nullptr;
            ComplexImage2D sampleImageOut(c_sampleSourceImageWidth, c_sampleSourceImageWidth);
            simple_fft::FFT(sampleImageIn, sampleImageOut, c_sampleSourceImageWidth, c_sampleSourceImageWidth, error);

            // show the frequencies
            char fileName[256];
            sprintf(fileName, "output/%s/samples/%s/%s%s_%s.png", sampleFunction.sampleFamily, sampleFunction.sampleType, fileNamePrefix, testName, sampleFunction.name);

            // get the magnitudes
            Image result(c_sampleSourceImageWidth, c_sampleSourceImageWidth);
            const complex_type* src = sampleImageOut.pixels.data();
            PixelRGBAF32_PMA* dest = result.m_pixels.data();
            float maxMag = 0.0f;
            for (size_t y = 0; y < c_sampleSourceImageWidth; ++y)
            {
                for (size_t x = 0; x < c_sampleSourceImageWidth; ++x)
                {
                    const complex_type& c = *src;
                    float mag = float(sqrt(c.real()*c.real() + c.imag()*c.imag()));
                    maxMag = std::max(mag, maxMag);
                    *dest = PixelRGBAF32_PMA(PixelRGBAF32{mag, mag, mag, 1.0f});
                    ++src;
                    ++dest;
                }
            }

            // normalize the magnitudes
            dest = result.m_pixels.data();
            for (size_t y = 0; y < c_sampleSourceImageWidth; ++y)
            {
                for (size_t x = 0; x < c_sampleSourceImageWidth; ++x)
                {
                    dest->r /= maxMag;
                    dest->g /= maxMag;
                    dest->b /= maxMag;
                    ++dest;
                }
            }

            // save the image
            SaveImage(result, fileName);
        }
    }
}

// TODO: need to offset the image by half, so DC is in the center.
// TODO: we may not need such a large image. Probably won't know until we have more sample types analyzed though.