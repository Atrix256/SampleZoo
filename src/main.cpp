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
    _1d::Tests::AutoTest();
    _2d::Tests::AutoTest();
    ManualTest();

    DataCache::Save();
    return 0;
}

/*
TODOs:

* sobol indexes out of range! need to fix. true for 2d, not sure if true for 1d.
 * it's because you were adding 1 to the index, to make it skip zero.  see if you can figure out if you added that or if it's correct (re-read your blog post too perhaps)
 * if it's ok to not do that, you have it fixed and can delete this


* make 2d/1d tests deal with randomized sequences appropriately? (integration might be hard... lots of samples needing to be generated. hard for blue noise)
 * i wonder if the blue noise speedup idea you have would be any better? not for 2d....
 * maybe just have discrepancy deal with randomization. integration has lots of samples so kinda handles randomization in that sense already.

* I don't think hammersley bit truncation is working correctly.  In 8 samples, truncating 1 bit makes there be 4 unique samples.

? is hammerlsey ok with tests doing non power of 2 sample counts on it? i think probably not, but check it out.


* there are a lot of disk sampling and other things in the progressive projective blue noise code.
* reread for 2d sequences: http://extremelearning.com.au/unreasonable-effectiveness-of-quasirandom-sequences/


Docs:
! hammersley: if you skip index 0, it doesn't help anything, because you then get the zero from the next sequence! This unless you do N-1 sample items, which is kind of weird and doesn't really help anything.
* n rooks -> followed regular centered offset best practices

* centralize all explanations that you can.
 * link to them from the family specific pages
 * make the family specific pages be about technical details specific to that family.

*/