/*
FILE: main.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019
*/

#define _CRT_SECURE_NO_WARNINGS // for stb

#include <stdio.h>

#include "samples/samples.h"
#include "tests/tests.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

int main(int argc, char **argv)
{
    std::vector<float> samples;
    FILE* file = fopen("output/samples/1d/regular/discrepancy.txt", "w+b");

    Samples::_1d::Regular::Regular(samples, 16);
    Tests::_1d::Numberline::MakeNumberline("output/samples/1d/regular/regular.png", samples, 512);

    fprintf(file, "%zu samples\r\n\r\n", samples.size());

    fprintf(file, "Regular:\r\n  Discrepancy: %0.2f\r\n  Wrap: %0.2f\r\n\r\n",
        Tests::_1d::Discrepancy::CalculateDiscrepancy(samples),
        Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(samples)
    );

    Samples::_1d::Regular::RegularCentered(samples, 16);
    Tests::_1d::Numberline::MakeNumberline("output/samples/1d/regular/regularcentered.png", samples, 512);

    fprintf(file, "RegularCentered:\r\n  Discrepancy: %0.2f\r\n  Wrap: %0.2f\r\n\r\n",
        Tests::_1d::Discrepancy::CalculateDiscrepancy(samples),
        Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(samples)
    );

    Samples::_1d::Regular::RegularCenteredOffset(samples, 16);
    Tests::_1d::Numberline::MakeNumberline("output/samples/1d/regular/regularcenteredoffset.png", samples, 512);

    fprintf(file, "RegularCenteredOffset:\r\n  Discrepancy: %0.2f\r\n  Wrap: %0.2f\r\n\r\n",
        Tests::_1d::Discrepancy::CalculateDiscrepancy(samples),
        Tests::_1d::Discrepancy::CalculateDiscrepancyWrapAround(samples)
    );

    fclose(file);

    return 0;
}

/*
TODO:
* make the test above be a "conglomerate test" and put it in the tests folder w/ documentation

* clean up non torroidal discrepancy calculation? even just the comments maybe?
 * add a 0.0 and 1.0 before sorting and then do it by index.

* sampling: golden ratio next? it's progressive, so is a bit special in that way.
 * maybe do white noise next? white noise is also progressive
 * blue noise? mitchell's best candidate. add todos: poisson disk, relaxation.

* show how regular sampling has problems with aliasing (and how random samples don't, but have noise)
* add numerical integration tests to 1d sample tests: linear, step, e^x? from 0 to 1
 * compare vs high count uniform random


? open up "1d sampling" to submissions soon, and have a page about how to do it?

Documentation WIP:

Guidelines overall:
* Code should be copy / paste-able
* Prefer readability over efficiency
* Comments are good

Guidelines for 1d sampling submissions:
* generate values to sample in [0,1]
* stateless one shot generation: function signature requirements
* progressive: derive from a class that has a pure virtual to implement. So, you can have state if you want to, but don't have to i guess?
 * would need to hook up to different tests
* random: store random parts in a cache? dunno...
* make .h and a .cpp.
 * naming conventions! of files, namespaces, directories
 * keep the header as minimal as possible to keep from poluting global symbols.
 * include your .h in the _1d.h file

*/