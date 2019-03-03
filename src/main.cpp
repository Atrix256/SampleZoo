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

* cache all samples in memory, even if not on disk
 * have some auto gen'd code tell the data cache which keys to actually save, but always use the cache otherwise.
 * nice for blue noise which is still slow enough to matter.
 * do this before turning off cache usage for blue noise

 * printf after each sample function in testing functions

* document: how to submit a 2d sampling type or test?
* make blue noise faster with a sorted list and binary search. shouldn't need to cache samples then.
* show progress: print out what tests it's doing and some % of total tests done? make it be part of the generated code.

* James has a bluenoise type sampling he wants to contribute called dpp. Hit him up when you are ready to open things up!

* try resetting unique index back to 1 and rng back to seed after every test.
 * should help cache, and also make different tests more consistent.

* text: i think the left side baseline is important. read that 16x aa blog post (part 3)
* discrepancy should have multiple tests for randomized samples, and so should integration. numberline doesn't care though.

 ! gather links from progressive projective blue noise project! there are some good ones.
 * and email later.





Documentation WIP:

Guidelines overall:
* samples are in [0,1)^N in general and similar. If you have a good reason to diverge from that, you can. might be worth a new sample family?
* Code should ideally be copy / paste-able for easy drop in use. modular / standalone to be low effort to take & use.
* Prefer readability over efficiency. STL is fine.
* Comments are good
* snake case file names
* upper camel case function names, name space names
* The purpose of sample specific documentation is two fold...
 1) Make programmers (non mathematicians) able to understand how it works.
 2) Show how it works, as well as any choices or trade offs there may be.
 * NOTE: comparison vs other sequences is usually out of scope of a sample submission, and should be made into a special test type, which you can link to.

Guidelines for 1d sampling submissions:
* generate values to sample in [0,1)
* make a subfolder in src/samples/_1d/.  The subfolder name is snake case.
 * add your code (multiple cpps and headers are allowed)
 * make an info.lua
* run premake and it will make a .h file that is named the same as the subfolder that exposes the functions you listed in your info.lua file.
 * it will also update the header files to include this header file.
* The namespace is named off of "code name" in the .lua file.  It should be the same as the subfolder name but upper camel case instead of snake case.
! TODO: talk about documentation md file.
! update this.
 * I think you might have to run premake after running the auto tests?

*/