// Autogenerated by codegen.lua during premake process

#pragma once

#include "irrational_numbers/irrational_numbers.h"
#include "irrational_numbers/autotest.h"
#include "LDS/LDS.h"
#include "LDS/autotest.h"
#include "regular/regular.h"
#include "regular/autotest.h"
#include "uniform_random/uniform_random.h"
#include "uniform_random/autotest.h"

namespace Samples
{
    namespace _1d
    {
        inline void AutoTest(void)
        {
            IrrationalNumbers::AutoTest();
            LDS::AutoTest();
            Regular::AutoTest();
            UniformRandom::AutoTest();
        }
    }
}
