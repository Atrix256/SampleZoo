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
    // Any modifications you make to those files will be undone when you run premake and re-generate code and documentation.
    //_1d::Tests::AutoTest();
    _2d::Tests::AutoTest();
    //ManualTest();

    DataCache::Save();
    return 0;
}

/*
TODOs:

* uncomment 1d tests and manual tests before merging branch 
 * adding 2d auto tests makes manual tests have different results. why? rng should be reset etc. should be the same.

* Get LDS types from your page
* also progressive projective blue noise?
* make documentation for plot test and uniform random
* do DFT test and make documentation

*/