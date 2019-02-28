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

void _1d::Tests::DFT::DFT(const std::vector<std::vector<SampleGenerateInfo_1d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
    static const int c_numSamples = 128;
    static const int c_sampleSourceImageWidth = 1024;

    for (const std::vector<SampleGenerateInfo_1d>& sampleType : sampleFunctions)
    {
        for (const SampleGenerateInfo_1d& sampleFunction : sampleType)
        {
            size_t numTests = sampleFunction.randomized ? 10000 : 1;

            std::vector<float> min(c_sampleSourceImageWidth, FLT_MAX);
            std::vector<float> max(c_sampleSourceImageWidth, -FLT_MAX);
            std::vector<float> avg(c_sampleSourceImageWidth, 0.0f);
            std::vector<float> last(c_sampleSourceImageWidth, 0.0f);

            for (size_t testIndex = 0; testIndex < numTests; ++testIndex)
            {
                // get the samples
                std::vector<float> samples;
                sampleFunction.function(samples, c_numSamples, sampleFunction.cacheKey, sampleFunction.randomized);

                // make a black and white image of the samples
                std::vector<complex_type> sampleImage(c_sampleSourceImageWidth, real_type(0.0f));
                for (float f : samples)
                {
                    size_t index = Clamp(size_t(f * float(c_sampleSourceImageWidth) + 0.5f), size_t(0), size_t(c_sampleSourceImageWidth - 1));
                    sampleImage[index] = 1.0f;
                }

                // DFT the image to get frequency of the samples
                const char* error = nullptr;
                simple_fft::FFT(sampleImage, sampleImage.size(), error);

                for (size_t i = 0; i < sampleImage.size(); ++i)
                {
                    const complex_type& c = sampleImage[i];
                    float mag = float(sqrt(c.real()*c.real() + c.imag()*c.imag()));

                    min[i] = std::min(min[i], mag);
                    max[i] = std::max(max[i], mag);
                    avg[i] = Lerp(avg[i], mag, 1.0f / float(testIndex + 1));
                    last[i] = mag;
                }
            }

            // make a graph of the frequencies
            char fileName[256];
            sprintf(fileName, "output/%s/samples/%s/%s%s_%s.png", sampleFunction.sampleFamily, sampleFunction.sampleType, fileNamePrefix, testName, sampleFunction.name);
            GraphDesc desc;
            desc.fileName = fileName;
            desc.xAxisTicks.push_back({ 0.0f, "0 hz", TextHAlign::Left, TextVAlign::Top });

            if (sampleFunction.randomized)
            {
                char title[256];
                sprintf(title, "DFT Magnitude: %s %zu tests", sampleFunction.name, numTests);
                desc.title = title;
                desc.graphItems.resize(desc.graphItems.size() + 3);
                GraphItem& dftDataMin = desc.graphItems[desc.graphItems.size() - 3];
                GraphItem& dftDataMax = desc.graphItems[desc.graphItems.size() - 2];
                GraphItem& dftDataAvg = desc.graphItems[desc.graphItems.size() - 1];
                dftDataMin.label = "Minimum";
                dftDataMax.label = "Maximum";
                dftDataAvg.label = "Average";
                for (size_t i = 0; i < c_sampleSourceImageWidth; ++i)
                {
                    // buckets go eg: [0hz, 1hz, 2hz, 3hz, 4hz, -3hz, -2hz, -1hz]
                    float frequency = float(i);
                    if (i > c_sampleSourceImageWidth / 2)
                        frequency -= float(c_sampleSourceImageWidth);

                    dftDataMin.data.push_back(Vec2{ frequency, min[i] });
                    dftDataMax.data.push_back(Vec2{ frequency, max[i] });
                    dftDataAvg.data.push_back(Vec2{ frequency, avg[i] });
                }
            }
            else
            {
                char title[256];
                sprintf(title, "DFT Magnitude: %s", sampleFunction.name);
                desc.title = title;
                desc.graphItems.resize(desc.graphItems.size() + 1);
                GraphItem& dftData = desc.graphItems[desc.graphItems.size() - 1];
                for (size_t i = 0; i < c_sampleSourceImageWidth; ++i)
                {
                    // buckets go eg: [0hz, 1hz, 2hz, 3hz, 4hz, -3hz, -2hz, -1hz]
                    float frequency = float(i);
                    if (i > c_sampleSourceImageWidth / 2)
                        frequency -= float(c_sampleSourceImageWidth);

                    dftData.data.push_back(Vec2{ frequency, last[i] });
                }
            }
            MakeGraph(desc);
        }
    }
}