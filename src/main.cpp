/*
FILE: main.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019
*/

#include "codegen.h"

int main(int argc, char **argv)
{
    // Note: comment this out and call your specific code directly if you want to iterate on code.
    Tests::AutoTest();

    return 0;
}

/*
TODO:

* Martin's comments about graphing in Twitter dm
 * this is important. he has the right answers for improving the graphing

* make some 1d summary page: sobol vs golden ratio vs best candidate blue noise, vs regular centered offset?

* there's a thing about aliasing vs... (discrepancy?) i dunno. it was from one of the papers you have a link to.  see if you can formalize that into a test of some kind.

* document "regular jittered" and mention pixar.

* document van der corupt base 2, 3, 5 and mention stuff from https://blog.demofox.org/2017/05/29/when-random-numbers-are-too-random-low-discrepancy-sequences/

* note properties of sample types in the documentation. randomized / progressize.

* put in todos: could multithread the auto tests!

* progressive and non progressive sequences ...
 * should have integration graphed differently.  Progressive = partial sequence. Non progressive = full sequence.
 * should have discrepancy graphed differently?  ditto to above...
 * it would be nice to show them graphed wrong for 1 image to show the difference though.
 ! randomized sequences should be an average over several runs.

* likely need to cache blue noise results soon in a cache folder!

* make a way to specify specific tests you want to do.
 * like to compare the best of the best for numerical integration.
 * maybe make it a manually written thing that writes a specific file name, that you then link to from a manually made / linked to page?

 * make _1d be a parent folder everywhere, instead of a child under tests and samples.
  * this is a "sample family", and it contains both samples and tests.
  * i thought about not doing this, but the tests and samples assume they are interchangeable so go for it

* maybe force discrepancy graph (and integration error graph?) to have a min / max of 0 / 1?
 * that is the natural range of the graph, and that way it's easier to compare different graphs

* for the integration graph, could show the actual function graphed in the lower left.
 * put this on todo list

* martin has some great info about graph improvements in his DM on twitter. to match what was seen in the similar papers

* put in todo: make graph rendering better in general.
* circle instead of box for point plotting

* maybe numerical integration results should be loglog.
 * instead of drawing lines between all data points, maybe draw lines between data points evaluated per pixel on the graph.
 * where should the x axis tick marks go?

 ? more sampling types. esp low discrepancy, like from your blog

* need to make integration test "other scopes" and make documentation link to it.

* the error graphs aren't really showing very well. i'd try non long graphs but i think everything shrinks down to the axis.
 * maybe non log error graphs, but not as many sample points either?

* for integration test, should it graph the function it's integrating as well?
 * would need some auto test call into the test scope to do "one time" work

* White noise should do several tests and take the average
 * the test would know to do this because the sample type will say it's randomized

? does pi even converge on linear test?? maybe you have wrong integration result to calculate error by?

* for file names output by tests, maybe the test lua file just says which files they spit out, then it's up to the test to actually do so...
 1) All sample families
 2) A single sample family
 3) A single sample type
 * it will expect a specific name

* randomized sample types should be noted in the passed in data so they can be repeated some number of times.

* integration error graphs should also graph the expected convergence of white noise.  Check progressive projective blue noise project.

* why do the error graphs always start at 0.5 error? maybe it's from sampling at 0?
 * yeap!
 ! make the LDS (and whatever else appropriate) not start at index 0.
  * talk about it in the description too?
  * maybe have a golden ratio that does use index0 and another that doesn't.
 * "sure, having one sample less good isn't that big a deal when you are looking at the integration graphs, but if all you have is 8 samples like in realtimegraphicss, making one sample better makes a meaningful difference to the result."

* TODO: no drawing function should take pixel values. not even "font height" should be absolute.
 * DrawLinePx, DrawTextPx.
 * BlendInImage may be ok as px? dunno.
// TODO: BlendInImage should take an int, so things can start out of bounds on the negative side. make long text as a graph label and see what happens as a usage case

* things taking a float x/y should take a vec2 instead

? some way to limit tests to a specific test, or samples to a specific sample. easier for iteration in debug mode!
 * maybe a #define in main here?
 * a note in main.cpp above the autotest call: "commment this out and call your specific test if you want to iterate".
 ? how to isolate sample types though?
 * maybe a comment about going to the autogenerated code and commenting out the sample types you don't care about?

 * look for todo's in the code base before merge to master

 * text: i think the left side baseline is important. read that 16x aa blog post (part 3)

 "Vdc is regular sampling, but progressive, and sorted to be a binary search type setup"

* get a graph test working now that you have text.
 * maybe integration test would be good? i think make one graph for all sample functions in the same sample type?
 * need to change how docs are generated for that (and maybe code gen?)
 * make a function that graphs data you give it.
 * make a legend on the graph.
 * use golden ratio in HSV to turn index into colors.

* maybe interpolate the numberline using HSV to keep brightness or make it look better in general? not sure.
 * we have hsv code now. try it!

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


! need to make sure all documentation is good (hand written). both present, and working w/ new image links etc.



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