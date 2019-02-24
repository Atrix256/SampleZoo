/*
FILE: dft.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/23/2019
*/

#include "codegen.h"
#include "shared/image.h"
#include "shared/graph.h"
#include "shared/math.h"
#include "simple_fft/fft_settings.h"
#include "simple_fft/fft.h"
#include <vector>

void _1d::Tests::DFT::DFT(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName)
{
    static const int c_numSamples = 128;
    static const int c_sampleSourceImageWidth = 1024;

    for (const std::vector<SampleGenerateInfo_1d>& sampleType : sampleFunctions)
    {
        for (const SampleGenerateInfo_1d& sampleFunction : sampleType)
        {
            // get the samples
            std::vector<float> samples;
            sampleFunction.function(samples, c_numSamples);

            // make a black and white image of the samples
            std::vector<complex_type> sampleImage(c_sampleSourceImageWidth*2, real_type(0.0f));
            for (float f : samples)
            {
                size_t index = Clamp(size_t(f * float(c_sampleSourceImageWidth * 2) + 0.5f), size_t(0), size_t(c_sampleSourceImageWidth * 2 - 1));
                sampleImage[index] = 1.0f;
            }

            // DFT the image to get frequency of the samples
            const char* error = nullptr;
            simple_fft::FFT(sampleImage, sampleImage.size(), error);

            // make a graph of the frequencies
            char fileName[256];
            sprintf(fileName, "output/%s/samples/%s/%s_%s.png", sampleFunction.sampleFamily, sampleFunction.sampleType, testName, sampleFunction.name);
            char title[256];
            sprintf(title, "DFT Magnitude: %s", sampleFunction.name);
            GraphDesc desc;
            desc.fileName = fileName;
            desc.title = title;
            desc.graphItems.resize(desc.graphItems.size() + 1);
            desc.xAxisTicks.push_back({ 1.0f, "1 hz", TextHAlign::Left, TextVAlign::Top });
            GraphItem& dftData = *desc.graphItems.rbegin();
            for (size_t i = 1; i < sampleImage.size() / 2; ++i)
            {
                const complex_type& c = sampleImage[i];
                float mag = float(sqrt(c.real()*c.real() + c.imag()*c.imag()));
                dftData.data.push_back(Vec2{float(i), float(mag)});
            }
            MakeGraph(desc);

            /*
            Image tempTest(c_sampleSourceImageWidth * 2, 1);
            for (float f : samples)
            {
                size_t index = Clamp(size_t(f * float(c_sampleSourceImageWidth * 2) + 0.5f), size_t(0), size_t(c_sampleSourceImageWidth * 2 - 1));
                tempTest.m_pixels[index] = {0.0f, 0.0f, 0.0f, 1.0f};
            }
            sprintf(fileName, "output/%s/samples/%s/%s_%s_samples.png", sampleFunction.sampleFamily, sampleFunction.sampleType, testName, sampleFunction.name);
            SaveImage(tempTest, fileName);
            */
        }
    }
}