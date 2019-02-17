/*
FILE: main.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019
*/

#include "codegen.h"

#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

// TODO: temp! make this automatic, and run the autotest like you did before for samples.
#include "tests\_1d\numberline\autotest.h"
#include "tests\_1d\integration\autotest.h"

#include "shared/drawtext.h"

int main(int argc, char **argv)
{
    Image image = MakeTextImage("Hello World", { 1.0f, 0.2f, 0.5f, 0.75f }, 45.0f);
    SaveImage(image, "yo.png");

    // TODO: make a root function in tests or something, that runs all the auto tests?
    //Tests::_1d::Numberline::AutoTest();
    Tests::_1d::Integration::AutoTest();

    return 0;
}

/*
TODO:

? some way to limit tests to a specific test, or samples to a specific sample. easier for iteration in debug mode!
 * maybe a #define in main here?

* get a graph test working now that you have text.
 * maybe integration test would be good? i think make one graph for all sample functions in the same sample type?
 * need to change how docs are generated for that (and maybe code gen?)
 * make a function that graphs data you give it.
 * make a legend on the graph.
 * use golden ratio in HSV to turn index into colors.

* maybe interpolate the numberline using HSV to keep brightness or make it look better in general? not sure.

* next: get other tests working and making their results.md files
 * figure out the right sample counts for each test

* link to blue noise paper about mitchell's best candidate:
 * "Spectrally Optimal Sampling for Distribution Ray Tracing" by Don P. Mitchell 1991
 * http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.556.445&rep=rep1&type=pdf

 * 1d dft test

* do these for LDS, and also link to from LDS
 * https://twitter.com/TechSparx/status/1096394113635753984?s=03
 * http://extremelearning.com.au/going-beyond-golden-ratio/
 * also your own ones: https://blog.demofox.org/2017/05/29/when-random-numbers-are-too-random-low-discrepancy-sequences/

 * Use golden ratio index to color for line graphs, and mention it in the golden ratio section.
  * and link to the page that shows how to do it

* integration test: include y=x^3

* can we make some special "meta tests" to combine information?

 * make sampleFunctions etc const in test function signatures

 * Histogram test. Check white noise at large sample counts! Maybe 10, 100, 1000, etc

* make tests have autotest.h files which run through all sample types in the same family, at the specified number of samples.

* James has a bluenoise type sampling he wants to contribute called dpp. Hit him up when you are ready to open things up!

* make sure mitchell's best candidate is using torroidal distance between points.

* Golden ratio: link to generating unique colors with GR

* could cache expensive to calculate sequences, and check that cached data in

* do integration tests
 * add more!
 * make it graph them!

 * make documentation for Sobol in LDS sample type
  * and integration test
  * and standard test

? is blue noise less predictable than white? do tests to find out!

* make some better tests that actually show things:
 * discrepancy as a graph with number of samples
 * integration error over time vs specific functions

* clean this up below & figure out what is needed to open this up to letting people submit 1d sample sequences!
 * purpose of samples and test documentation?
 * automated testing setup / comparisong testing?

 ? how does testing a progressive sequence differ from non progressive?
 * show a graph of discrepancy over sample count, to see how it changes.
 * somehow need to note that it's progressive - in documenation, and also in code?
 * for now, it's not treated as progressive or noted as progressive.

? open up "1d sampling" to submissions soon, and have a page about how to make submissions
 * figure out what exactly you want to do before opening it up




Documentation WIP:

Guidelines overall:
* samples are in [0,1)^N in general and similar. If you have a good reason to diverge from that, you can.
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