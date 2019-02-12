/*
FILE: main.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019
*/

#define _CRT_SECURE_NO_WARNINGS // for stb

#include <stdio.h>

#include "tests/tests.h"
#include "samples/samples.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"


int main(int argc, char **argv)
{
    Samples::AutoTest();
    return 0;
}

/*
TODO:

* make tests autogenerate a header, from the info.lua file, like samples do

* make sure documentation still works. you changed some file names!

* standardize the samplefamily.lua and info.lua files.  (maybe 2nd one should be sample.lua?)
 * consistent naming convention
 * also maybe sampleType and subSampleType should be called sampleFamily and something else
 * functions or table? if that should be standardized...

 * make documentation for uniform random tests
  * and LDS (sobol only right now, maybe add more?)


* clean this up below & figure out what is needed to open this up to letting people submit 1d sample sequences!
 * purpose of samples and test documentation?
 * automated testing setup / comparisong testing?

* mention somewhere that all samples are in [0,1) unless otherwise stated.


? how does testing a progressive sequence differ from non progressive?
 * show a graph of discrepancy over sample count, to see how it changes.
 * somehow need to note that it's progressive - in documenation, and also in code?
 * for now, it's not treated as progressive or noted as progressive.

* make the test above be a "conglomerate test" and put it in the tests folder w/ documentation
 * make it auto generated from information in a lua file?
 * specify the functions to call, and if they are progressive or what.
 * for irrational tests, can pass extra params as template params (like rational number etc).

* sampling: golden ratio next? it's progressive, so is a bit special in that way.
 * maybe do white noise next? white noise is also progressive
 * blue noise? mitchell's best candidate. add todos for blue noise: poisson disk, relaxation.

? open up "1d sampling" to submissions soon, and have a page about how to make submissions
 * figure out what exactly you want to do before opening it up

* look into generating header files and documentation from lua scripts called from in premake
 * maybe tests too, and have sequences specify a "json" like file (but lua?) about their properties: progressive, randomized, etc?


 * need some larger tests showing irrational vs regular sampling. things like discrepancy for sample count.
  * automatically generate test code based on a lua file describing properties of the sampling would be really nice.


* add to blue noise notes... blue noise from eigenvectors
 * https://twitter.com/TechSparx/status/1093902404867760129

* make numberlines have a bool to have nodes be a color based on index? to show progressive sequences.
 * maybe always want it on? not sure.



Documentation WIP:

Guidelines overall:
* Code should be copy / paste-able for easy drop in use.
* Prefer readability over efficiency. STL is fine.
* Comments are good
* snake case file names
* upper camel case function names, name space names
* The purpose of sample specific documentation is two fold...
 1) Make programmers (non mathematicians) able to understand how it works
 2) Show how it works, as well as any choices or trade offs there may be.
 * NOTE: comparison vs other sequences is usually out of scope, and should be made into a special test type, which you can link to.

Guidelines for 1d sampling submissions:
* generate values to sample in [0,1)
* make a subfolder in src/samples/_1d/.  The subfolder name is snake case.
 * add your code (multiple cpps and headers are allowed)
 * make an info.lua
* run premake and it will make a .h file that is named the same as the subfolder that exposes the functions you listed in your info.lua file.
 * it will also update the header files to include this header file.
* The namespace is named off of "code name" in the .lua file.  It should be the same as the subfolder name but upper camel case instead of snake case.
! TODO: talk about documentation md file.

*/