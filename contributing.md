# Contributing

I'm currently fleshing things out and will soon have a standardized process for submitting sampling patterns and sampling tests.

Please check back later!

## Crediting Work

Everyone who contributes code or non code contributions of any size are elligable to be included in the [Credits](credits.md) page.

Feel free to add your own name to the appropriate section with your pull request.

If you are making a code change, also feel free to add your name as a contributor to whatever files you modify.

## Non Code Contributions

Both code and non code contributions are valued by this project.

Non code contributions include things like the below:
* Terminology corrections.
* Editorial corrections to documentation.
* Improving explanations about sampling or tests types, including adding links to relevant resources.
* supplying links and/or information about testing and/or sampling types to be included.

## Source Code Header (Strongly Suggested)

It's strongly suggested that all files submitted have a header like the below.  All fields are optional however and there are no specific rules about date format, order of fields, or similar.

If you make a change to a file, feel free to add your name to the contributors section, regardless of the size of the change.

You can specify a license as part of this header as shown below.  If no license is supplied, the file will fall under the default license of this repo, which is the [MIT License](LICENSE).

```cpp
/*
FILE: ProgProjBlueNoise.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/8/2019
LICENSE: MIT (see license.md next to this file)

CONTRIBUTORS: 
Jim Bean
Jack Daniels

LOG:
2/8/19 - Created the file (Alan Wolfe)
*/
```
## Work Needed

A list of specific things the project needs.

### Infrastructure
* a better way to find files in codegen.lua than using ls since some systems won't have it. os.matchdirs:  https://github.com/premake/premake-core/wiki/os.matchdirs
* centralize random number (white noise) generation, also make it seedable for deterministic results.
* clang tidy for style guidelines? Or google C++ style guide? or clang-format? "clang-format -style=google"
* also an editor config? https://editorconfig.org/
* improve the look of graphing in general, all graphs.
* Do super sampling of graphs to help aliasing problems: render at a larger resolution and downside. Possibly render stochastically?
* This seems possibly useful for automatically putting ticks on graphs: http://vis.stanford.edu/files/2010-TickLabels-InfoVis.pdf
* I think you can set up CI as well as code tidying in github. Need to figure those things out.
* Make a way to cache data, since some of it takes a long time to generate (eg large counts of blue noise)
* probably should modify best candidate blue noise generation to use a (1d) grid acceleration structure. Or sort the points and use binary search to calculate distances or something.
* graph: make axis labels instead of using footer text

### 1D Sampling Patterns & Tests
* more irrational numbers such as the silver ratio and the plastic constant. Just meaningful irrational numbers though. 
* low discrepancy sequences (basic, more exotic, scrambled, etc!)
* other 1d blue noise methods including: poisson disk, relaxation.
* blue noise from eigenvectors: https://twitter.com/TechSparx/status/1093902404867760129
* jittered grid
* other 1d sampling patterns not listed here!
* frequency analysis (DFT)
* regular sampling and some others are not progressive. for integration graphing, it's useful to show what that means when tested the same way progressive samples are tested, but i think non progressive sampling types should be graphed such that at sample count N, it's showing the error for an N count sequence.
* on the integration error graph, the actual graph being integrated could be shown in the lower left

## Work Needed, but claimed by Alan for now

### Infrastructure
* make a standard for how to add new samples or tests, fill it out in the contributing file.
* make a data cache for expensive to compute things (eg blue noise)

### Sampling Patterns
* 2d basic LDS and others
* Martin's R2 sequence for 2d (and higher dimensions)
* uniform random point in triangle: https://twitter.com/TechSparx/status/1093193006440726529?s=03
* prorgressive projective blue noise & all the papers you have linked etc.
* dither / animated dither blue noise, ign, etc
* sampling on a sphere
* sampling in a triangle

### Sampling Tests
* 2d tests and beyond.
* show how regular 1d sampling has aliasing problems. Also show how random samples trade the aliasing for noise. 
* correlated multi jittering: https://graphics.pixar.com/library/MultiJitteredSampling/paper.pdf
