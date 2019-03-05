/*
FILE: integration.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 3/4/2019

Description:
Uses samples to integrate 2d functions
*/

#include "codegen.h"
#include "shared/math.h"
#include "shared/graph.h"

static const float c_pi = 3.14159265359f;

static const float c_referenceValue_Disk = 0.5f;
static const float c_referenceValue_Triangle = 0.5f;
static const float c_referenceValue_Step = 1.0f / c_pi;
static const float c_referenceValue_Gaussian = c_pi / 4.0f * (float)erf(1.0) * (float)erf(1.0);
static const float c_referenceValue_Bilinear = 0.25f;

void _2d::Tests::Integration::Disk(const std::vector<std::vector<SampleGenerateInfo_2d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
}

void _2d::Tests::Integration::Triangle(const std::vector<std::vector<SampleGenerateInfo_2d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
}

void _2d::Tests::Integration::Step(const std::vector<std::vector<SampleGenerateInfo_2d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
}

void _2d::Tests::Integration::Gaussian(const std::vector<std::vector<SampleGenerateInfo_2d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
}

void _2d::Tests::Integration::Bilinear(const std::vector<std::vector<SampleGenerateInfo_2d>>& sampleFunctions, const char* testName, const char* fileNamePrefix)
{
}

// TODO: continue!
