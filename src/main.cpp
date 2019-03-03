/*
FILE: main.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019
*/

#include "shared/datacache.h"
#include "codegen.h"

#include "families/_1d/samples/blue_noise/manual_test.h"

void ManualTest()
{
    _1d::Samples::BlueNoise::ManualTest();
}

int main(int argc, char **argv)
{
    DataCache::Load();

    // Note: comment this out and call your specific code directly if you want to iterate on code.
    // You can also pop open samples.cpp and comment out sampling types .
    // You can also follow this function call down to see what is actually called and comment out the tests (or family of tests) that you don't want it to do while you iterate.
    // Note that any modifications you make to those files will be undone when you run premake and re-generate code and documentation.
    AutoTest();
    ManualTest();

    DataCache::Save();
    return 0;
}

/*
TODO:

* James has a bluenoise type sampling he wants to contribute called dpp. Hit him up when you are ready to open things up!

* discrepancy should have multiple tests for randomized samples, and so should integration. numberline doesn't care though.

* 2d sampling real soon. That's where the good stuff is.

*/