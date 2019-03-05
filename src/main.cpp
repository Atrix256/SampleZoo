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

? integration test soon?
* discrepancy test soon.

* I don't think hammersley bit truncation is working correctly.  In 8 samples, truncating 1 bit makes there be 4 unique samples.

? is hammerlsey ok with tests doing non power of 2 sample counts on it? i think probably not, but check it out.
* sobol indexes out of range! need to fix. true for 2d, not sure if true for 1d.


* reread for 2d sequences: http://extremelearning.com.au/unreasonable-effectiveness-of-quasirandom-sequences/


Docs:
! hammersley: if you skip index 0, it doesn't help anything, because you then get the zero from the next sequence! This unless you do N-1 sample items, which is kind of weird and doesn't really help anything.
* n rooks -> followed regular centered offset best practices

*/