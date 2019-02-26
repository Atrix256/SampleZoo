/*
FILE: main.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019
*/

#include "shared/datacache.h"
#include "codegen.h"

int main(int argc, char **argv)
{
    DataCache::Load();

    // Note: comment this out and call your specific code directly if you want to iterate on code.
    // You can also pop open samples.cpp and comment out sampling types (running premake regenerates samples.cpp and you will lose your changes FYI)
    // You can also follow this function call down to see what is actually called and comment out the tests (or family of tests) that you don't want it to do while you iterate.
    AutoTest();

    //std::vector<float> values;
    //DataCache::Instance().m_samples__1d.GetSamples_Progressive("blue_noise::BestCandidateRefined", _1d::Samples::BlueNoise::BestCandidateRefined, values, 4, true, false);

    DataCache::Save();
    return 0;
}

/*
TODO:


----- BEFORE RELEASE -----

? why does the cache.dat file change every run? it should be stable!

* maybe get documentation in order, and whatever ad hoc tests you need to set up for that, and try and announce sample zoo?
 * TOC probably needs to be more prevelant too.
 * organize the below into before announce vs after.  I think non progressive data cache and averaging multiple runs of randomized samples can wait til after.

 * explain dft test
 * in blue noise explanation show white vs blue DFT and how blue is missing low frequency content
 * and compare vs jittered.

! maybe need a "blue noise" meta page?
 * show DFT best candidate, vs uniform random, vs the regular jittered

* generate the TOC into the readme, by having the readme have a source .md file, and a marker for where to put the TOC
 * can still link to a raw TOC i guess :P

* mention how VDC2 (in a full power of 2) is regular sampling but in a binary search pattern

* document "regular jittered" and mention pixar.

* document van der corupt base 2, 3, 5 and mention stuff from https://blog.demofox.org/2017/05/29/when-random-numbers-are-too-random-low-discrepancy-sequences/

* link to blue noise paper about mitchell's best candidate:
 * "Spectrally Optimal Sampling for Distribution Ray Tracing" by Don P. Mitchell 1991
 * http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.556.445&rep=rep1&type=pdf

 * make documentation for Sobol in LDS sample type
  * and integration test
  * and standard test

? open up "1d sampling" to submissions soon, and have a page about how to make submissions
 * figure out what exactly you want to do before opening it up


! need to make sure all documentation is good (hand written). both present, and working w/ new image links etc.

----- STRETCH / UNSURE -----

* print out what tests it's doing and some % of total tests done? make it be part of the generated code.
* make sure both best candidate blue noises are based on torroidal distance
* discrepancy should have multiple tests for randomized samples, and so should integration. numberline doesn't care though.
* for manual tests, just have a .h file there in the tests folder defining the functions, implement them in the .cpp and manually include the .h and run the functioon in the manual tests
 * these are for the one off tests needed for documentation. maybe VDC5 should go here since it's a fail case? dunno.
* make some 1d summary page: sobol vs golden ratio vs best candidate blue noise, vs regular centered offset?
 * text: i think the left side baseline is important. read that 16x aa blog post (part 3)
* can we make some special "meta tests" to combine information?


----- AFTER RELEASE -----

* James has a bluenoise type sampling he wants to contribute called dpp. Hit him up when you are ready to open things up!

 * make sampleFunctions etc const in test function signatures

! on read failure of cache, clear out all the data i think.
 * or just don't insert the bad data? but exit because the rest of the file is likely corrupt

 ! gather links from progressive projective blue noise project! there are some good ones.
 * and email later.

 * try using left side bearing in the font drawing.  Sobol in particular has an issue but so does heljo, and RegularJittered

* there's a thing about aliasing vs discrepancy? i dunno. it was from one of the papers you have a link to.  see if you can formalize that into a test of some kind.
 * find the paper that talks about it

* for the purposes of documentation, it would be interesting to show non progressive sequences "graphed wrong" to show how the don't have good properties until the end.

* for the integration graph, could show the actual function graphed in the lower left.

? should integration error graphs (anywhere) show the expected convergence of white noise? check progressive projective blue noise project. maybe good for the documentation?

* maybe interpolate the numberline using HSV to keep brightness or make it look better in general? not sure.
 * we have hsv code now. try it!

* do these for LDS, and also link to from LDS
 * https://twitter.com/TechSparx/status/1096394113635753984?s=03
 * http://extremelearning.com.au/going-beyond-golden-ratio/
 * also your own ones: https://blog.demofox.org/2017/05/29/when-random-numbers-are-too-random-low-discrepancy-sequences/

 ? is blue noise more predictable than white? do tests to find out!







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