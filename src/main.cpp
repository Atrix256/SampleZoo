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
    Samples::_1d::Regular::Regular(samples, 16);
    Tests::_1d::Numberline::MakeNumberline("output/samples/1d/regular/regular.png", samples, 512);

    Samples::_1d::Regular::RegularCentered(samples, 16);
    Tests::_1d::Numberline::MakeNumberline("output/samples/1d/regular/regularcentered.png", samples, 512);

    Samples::_1d::Regular::RegularCenteredOffset(samples, 16);
    Tests::_1d::Numberline::MakeNumberline("output/samples/1d/regular/regularcenteredoffset.png", samples, 512);

    printf("Hello World!\n");
    return 0;
}

/*
TODO:

* make documentation for tests
* probably should have md files next to them, even if not much to say
* better (anti aliased) line drawing for number line. maybe make some shared code to do 2d drawing.
* maybe have DrawLine etc work in floating point units instead of absolute pixels
* link to numberline images from .md files!

Documentation WIP:

regular.md
* show the three sampling strategies on a number line. Maybe have images go into another folder?
* show them being used for some numerical integration tests of graphs? linear, step, e^x?  from 0 to 1.
* compare vs a high count uniform random
* show how regular sampling aliases.
* calculate and show discrepancy of values
* make a "unit test" type setup for regular.md that makes these things!

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