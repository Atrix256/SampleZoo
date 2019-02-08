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

* write up documentation for discrepancy test!
* calculate both torroidal and non torroidal discrepancy!
* put discrepancy values in for regular sampling.
* maybe link to the discrepancy testing page from the regular sampling page so people can read about discrepancy there

* clean up non torroidal discrepancy calculation? even just the comments maybe?

* sampling: golden ratio next? it's progressive, so is a bit special in that way.
 * maybe do white noise next?

* maybe have DrawLine etc work in floating point units instead of absolute pixels

* discrepancy docs: https://math.stackexchange.com/questions/1681562/how-to-calculate-discrepancy-of-a-sequence

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