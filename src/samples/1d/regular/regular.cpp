/*
FILE: regular.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019
*/

#include "regular.h"
using namespace Samples::_1d::Regular;

void Regular(std::vector<float>& values, size_t numValues)
{
    values.resize(numValues);
    for (size_t i = 0; i < numValues; ++i)
        values[i] = float(i) / float(numValues);
}

void RegularCentered(std::vector<float>& values, size_t numValues)
{
    values.resize(numValues);
    for (size_t i = 0; i < numValues; ++i)
        values[i] = float(i) / float(numValues - 1);
}

void RegularCenteredOffset(std::vector<float>& values, size_t numValues)
{
    float offset = 1.0f / float(numValues * 2);
    values.resize(numValues);
    for (size_t i = 0; i < numValues; ++i)
        values[i] = offset + float(i) / float(numValues);
}

/*
TODO:

regular.md
* show the three sampling strategies on a number line. Maybe have images go into another folder?
* show them being used for some numerical integration tests of graphs? linear, step, e^x?  from 0 to 1.
* compare vs a high count uniform random
* show how regular sampling aliases.

Guidelines overall:
* Code should be copy / paste-able
* Prefer readability over efficiency
* Comments are good

Guidelines for 1d sampling submissions:
* generate values to sample in [0,1]
* stateless one shot generation: function signature requirements
* progressive: derive from a class that has pure virtuals
* make .h and a .cpp.
 * naming conventions! of files, namespaces, directories
 * keep the header as minimal as possible to keep from poluting global symbols.
 * include your .h in the _1d.h file

*/