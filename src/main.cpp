/*
FILE: main.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019
*/

#include "shared/datacache.h"
#include "codegen.h"

#include "families/_1d/samples/blue_noise/manual_test.h"
#include "families/_1d/tests/integration/manual_test.h"
#include "families/_2d/tests/integration/manual_test.h"

void ManualTest()
{
    _1d::Tests::Integration::ManualTest();
    _1d::Samples::BlueNoise::ManualTest();
    _2d::Tests::Integration::ManualTest();
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

For sure:

* I'm finding conflicting info about what hammersley really even is. wikipedia says (1/k, halton).  Wolfram says (halton, reverse bits halton).

* hammersley paper (book) pdf from 1964
* http://www.cs.fsu.edu/~mascagni/Hammersley-Handscomb.pdf

* I don't think hammersley bit truncation is working correctly.  In 8 samples, truncating 1 bit makes there be 4 unique samples.
 * hammersley explanation: http://planning.cs.uiuc.edu/node210.html

? i dunno how bit truncation fits into hammersley

? is hammerlsey ok with tests doing non power of 2 sample counts on it? i think probably not, but check out what it's actually doing.

* add to todos to implement and analyze 2) (t,s)-sequences and (t,m,s)-nets; and 3) lattices

* there are a lot of disk sampling and other things in the progressive projective blue noise code.
* tests in 1d /2d: need to explain how they deal with randomization vs determinism and progressive vs non progressiveness
* test your links on each page, i think some are broken!

* make 2d/1d tests deal with randomized sequences appropriately? (integration might be hard... lots of samples needing to be generated. hard for blue noise)
 * i wonder if the blue noise speedup idea you have would be any better? not for 2d....
 * maybe just have discrepancy deal with randomization. integration has lots of samples so kinda handles randomization in that sense already.

Dunno:
* shrink the integration graphs?
* Make a 1d and 2d generic readme to explain when they are used and also to put hand picked global results and analysis in. intro section per family?
* samples in 1d / 2d: need a "comparison vs others" section. to showcase vs worse (worst?) and better (best?) of the family





Docs:
! hammersley: if you skip index 0, it doesn't help anything, because you then get the zero from the next sequence! This unless you do N-1 sample items, which is kind of weird and doesn't really help anything.
* n rooks -> followed regular centered offset best practices
* sobol: starts at index 1 because first sample is 0. Sound familiar?

* centralize all explanations that you can.
 * link to them from the family specific pages
 * make the family specific pages be about technical details specific to that family.

*/