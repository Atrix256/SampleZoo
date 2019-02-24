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
    static const int c_numSamples = 64;
    static const int c_sampleSourceImageWidth = 512;

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
            GraphDesc desc;
            desc.fileName = fileName;
            desc.graphItems.resize(desc.graphItems.size() + 1);
            GraphItem& dftData = *desc.graphItems.rbegin();
            for (size_t i = 0; i < sampleImage.size() / 2; ++i)
            {
                const complex_type& c = sampleImage[i];
                float mag = float(sqrt(c.real()*c.real() + c.imag()*c.imag()));
                dftData.data.push_back(Vec2{float(i), float(mag)});
            }
            MakeGraph(desc);

            int ijkl = 0;
            (void)ijkl;

            // TODO: x and y axis tick marks
            // TODO: only do first half of frequencies?
            // TODO: i think the graph needs to be shifted over.
        }
    }




    int ijkl = 0;
    //DoIntegrationTest(sampleFunctions, testName, ::Quadratic, 3.0f);
}