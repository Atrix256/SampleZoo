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


* I don't think hammersley bit truncation is working correctly.  In 8 samples, truncating 1 bit makes there be 4 unique samples.

! hammersley: if you skip index 0, it doesn't help anything, because you then get the zero from the next sequence! This unless you do N-1 sample items, which is kind of weird and doesn't really help anything.

? is hammerlsey ok with tests doing non power of 2 sample counts on it? i think probably not, but check it out.
* 2d "plot average" test? could have "average distance from center". Could also just draw a line showing how it moves around the center.. unknown.

* sobol indexes out of range! need to fix. true for 2d, not sure if true for 1d.
* should N rooks add a half? i think so... i think it should be like regular centered offset for best results.

* 2d plot test should project points down to x and y axis.
 ? should we do 1d tests on those projections? i think probably yes.

* add to todo for 2d tests:
 * radial power spectrum thing.
 * should randomized sequences go through multiple tests? or is radially averaging decent enough?

* uncomment 1d tests and manual tests before merging branch 
 * adding 2d auto tests makes manual tests have different results. why? rng should be reset etc. should be the same.

* regular grid
* jittered grid (stratified)
* R2
* latin squares? quincunx? n rooks, n queens?

* dart throwing in 1d and 2d

* 1d and 2d subrandom?

* Get LDS types from your page
* also progressive projective blue noise?
* make documentation for plot test and uniform random
* document dft test
* make discrepancy test
* document discrepancy test
* make and document integration test
? what other tests make sense?

*/