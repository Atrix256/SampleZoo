/*
FILE: standard.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/14/2019

Description:
A set of standard tests to compare 1d sequences against eachother
*/

#include "codegen.h"
#include "shared/math.h"

void Tests::_1d::Standard::Standard(SampleGenerate_1d sampleFunc, const char* sampleType, const char* subSampleType, const char* functionName)
{
    std::vector<float> samples;
    sampleFunc(samples, 16);
    FILE* file = fopen("output/samples/_1d/irrational_numbers/GoldenRatio.txt", "w+b");
    fprintf(file, "GoldenRatio %zu samples\r\n  Discrepancy: %0f\r\n  Wrap: %0f\r\n\r\n",
        samples.size(),
        Tests::_1d::Discrepancy::CalculateDiscrepancy(samples),
        Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(samples)
    );
    fclose(file);
    Tests::_1d::Numberline::MakeNumberline("output/samples/_1d/irrational_numbers/GoldenRatio.png", samples, 512);
    std::vector<float> integrationError;
    Tests::_1d::Integration::Linear(samples, integrationError);
}