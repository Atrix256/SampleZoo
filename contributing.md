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

A list of specific things the project needs

### Infrastructure
* make a standard for how to add new samples or tests, fill it out in the contributing file.
* gather your list of sampling patterns, tests, etc on this page. from progressive projective blue noise project and email etc.
* clang tidy for style guidelines? Or google C++ style guide? or clang-format? "clang-format -style=google"
* also an editor config? https://editorconfig.org/
* do some auto generation of parts of the documentation, in docgen.lua as part of the premake step, to help standardization and boilerplate

### Sampling Patterns
* 1d basic LDS
* 2d basic LDS
* Blue noise in 1d and 2d (and the various ways to generate it)
* Poisson Disk
* 1d and 2d jittered grid
* 1d golden ratio
* Martin's R2 sequence for 2d (and higher dimensions)

### Sampling Tests
* 1d discrepancy calculation.
* 1d numerical integration tests vs high sample count white noise.
* need other 1d tests and FFT! (FFTW?)
* 2d tests and beyond.
* show how regular 1d sampling has aliasing problems. Also show how random samples trade the aliasing for noise. 
* add numerical integration tests to 1d sample tests: linear, step, e^x? from 0 to 1.  compare vs high count uniform random as a ground truth.  Cache those results since they are costlier to compute?
