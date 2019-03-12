# Contributing

For a step by step walk through of how to contribute a new sampling sequence or a new sample sequence test, give this page a read:
[Contributing a Sequence or Test](contributesampletest.md)

For all other code changes, either submit a pull request, or drop me a line to chat details before you do work if you want a better chance of making sure your changes are accepted.

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
* make datacache use file compression (zlib?). The data makes this a very poor proposition. a 30MB data cache file compressed to 27MB for me.
* look into multithreading the tests & sample generation. data cache would need to be made safe for this.
* pcg variant or splitmix instead of mersenne twister, says Marc Reynolds.  Faster and higher quality.
* can we hash samples and test version or something somehow to know when we don't need to re-run a test if the target file already exists?
* add profile information to the output. We can instrument the autogen'd code to time sample functions and test functions and see where the time is going. Maybe also some custom markers if we want more specific information.
* save different caches to different files so they aren't such large binary diffs when anything changes.
* look into using markdeep (html w/ a header to use some javascript) instead of markdown for all this documentation.  Main readme might be markdown but the rest could be html? http://casual-effects.com/markdeep/#templates
* if the data cache gets too large, a way to get some space back is to not save lists of samples that are smaller than some threshold. 1d blue noise generates a lot for the dft for instance, that would be fairly quick to regenerate.
* whenever autogend docs label a test or sample, make a hyperlink to click to go to the page for it

### 1D Sampling Patterns & Tests
* more irrational numbers such as the silver ratio and the plastic constant. Just meaningful irrational numbers though. 
* low discrepancy sequences (basic, more exotic, scrambled, etc!)
* other 1d blue noise methods including: dart throwing, relaxation.
* blue noise from eigenvectors: https://twitter.com/TechSparx/status/1093902404867760129
* jittered grid
* other 1d sampling patterns not listed here!
* frequency analysis (DFT)
* regular sampling and some others are not progressive. for integration graphing, it's useful to show what that means when tested the same way progressive samples are tested, but i think non progressive sampling types should be graphed such that at sample count N, it's showing the error for an N count sequence.
* on the integration error graph, the actual graph being integrated could be shown in the lower left
* look into making a power spectrum test: https://cs.dartmouth.edu/wjarosz/publications/subr16fourier.html
* From paniq - could try a triangle or gaussian distribution on jittered grid.
* another number line test: graph sum of samples divided by count of samples.  Good #s of sample counts will have this value being near 0.5. It's the "expected value" of the sample set at that sample count.
* there is a 2d space of anti aliasing vs discrepancy for sampling types.  I know how to quantify discrepancy but not aliasing. maybe figure that out and plot the sequences on a graph showing where they lay here?
* for the integration graph, could show the actual function graphed in the lower left.
* silver ratio etc: http://extremelearning.com.au/going-beyond-golden-ratio/
* is blue noise more predictable than white noise? if in scope it could be interesting to make a test to show this.
* shuffle test for sequences.  graph histogram max-min to show balance of shuffle.  find some way to show how random a shuffle is. I thought graphing actual sample value would help but it's not easy to read.  awolfe/shuffletest has a partial implementation here.
* show how regular 1d sampling has aliasing problems. Also show how random samples trade the aliasing for noise. 
* discrepancy and integration tests should really do multiple tests for randomized samples.
* probably should do some rational samples to go with the irrational ones. easy enough to do and can show some interesting things.
* subrandom numbers? from your blog post.
* for 1d mitchells best candidate blue noise, instead of a binary search, since the samples are roughly even, could probably just find what % the sample is from 0-1 and linearly search from that % through the number list.  Maybe check and see if it's faster.

### 2d Sampling Patterns and tests
* best candidate.  Erin suggested kd tree with branch and bounds to find nearest point as an optimization. This would work better for 2d and beyond.
* progressive multijittered sequences (PMJ) - https://graphics.pixar.com/library/ProgressiveMultiJitteredSampling/pmj_slides.pdf
* correlated multi jittering: https://graphics.pixar.com/library/MultiJitteredSampling/paper.pdf
* Martin's R2 sequence for 2d (and higher dimensions) http://extremelearning.com.au/unreasonable-effectiveness-of-quasirandom-sequences/
* basic 2d LDS
* sampling on spheres and hemispheres
* making pmj02 more quickly: http://www.jcgt.org/published/0008/01/04/paper.pdf
* deterministic point process: https://arxiv.org/pdf/1207.6083.pdf and https://arxiv.org/pdf/1609.06840.pdf
* when someone requests regular sampling of 17 samples, what should we do? right now it does 4x4 and adds zero samples for the rest.
 * we should maybe find the most equal pair of factors that go into whatever number they asked for? not sure.
* dart throwing and other 2d blue noise sample point generation strategies.
* subrandom numbers? from your blog post.
* 2d "plot average" test? could have "average distance from center". Could also just draw a line showing how it moves around the center.. unknown. like the 1d numberline average test but for 2d.
* we could do (selected?) 1d tests on the projections of the 2d sampling patterns.
* latin squares? quincunx?, n queens?
* should randomized sequences go through multiple tests and report avg, min, max?
* projective blue noise
* your progressive projective blue noise
* this O(N) non progressive blue noise technique from Robert Bridson: https://www.jasondavies.com/poisson-disc/  (https://www.cs.ubc.ca/~rbridson/docs/bridson-siggraph07-poissondisk.pdf)

### Sphere sampling patterns
* http://extremelearning.com.au/how-to-generate-uniformly-random-points-on-n-spheres-and-n-balls/
* fib on spheres and caps: http://marc-b-reynolds.github.io/math/2018/06/21/SFPoints4ET.html
* points on a sphere: https://www.cmu.edu/biolphys/deserno/pdf/sphere_equi.pdf

### Circle sampling patterns
* Vogel Disk: https://www.gamedev.net/articles/programming/graphics/contact-hardening-soft-shadows-made-fast-r4906/
* to dft, try this? Reverse the random point in disk thing.  Polar but squared distances.  Dft the resulting points in square!
* sampling on disks and spheres: https://github.com/matt77hias/fibpy

### Triangle sampling patterns
* https://pharr.org/matt/blog/2019/02/27/triangle-sampling-1.html
* uniform point in triangle: https://twitter.com/TechSparx/status/1093193006440726529?s=03
* https://twitter.com/eric_heitz/status/1105097492964741120?s=03
* can do blue noise and white noise via rejection sampling

### 1d dithering patterns
* as a gateway to 2d dithering patterns.
* 1d dithering is like dice rolls over time (could look at blue vs white noise dice rolls!)
* explain relationship between dithering and integration (temporal integration)

### 2d Dithering Patterns
* ign
* void and cluster
* bayer
* from paniq for blue noise: basically: fill a square image with uniform noise, stencil out a center circle with feathering, take an inverse FFT and tada, blue noise
* Cover dithering and triangle distributed noise? and the things here: http://bartwronski.com/2016/10/30/dithering-part-three-real-world-2d-quantization-dithering/
* Animated dithering is something different than static dithering. Then can do taa and not, etc.
* Talk about how dithering relates to sample points.
* 2d sample points: (x,y)=f(x)
* 2d do: z=f(x,y)
* ?how does 1d dithering differ from 1d sample points? An important question to answer to clear some things up.
* 2d sample points: when you have a 2d region you need to take samples of.
* 2d dithering: when you have 2d data that you need to decrease precision on.
* Integration comes up in dithering when you animate it.
* Fewer bits to represent a higher bit depth. Either Integrate it explicitly (actually, or with taa), or let display / eyes integrate it.
* Talk about ordered dithering and thresholding.

### Documentation
* mention how sampling is like convolution in frequency space somewhere?
* explain progressive vs non progressive sequences
* maybe an overview page for 1d sampling, saying what is best at what?
* maybe a 1d page explaining a good order to read things in to best understand them?

### Research (read these, turn them into todos)
* look into this for rank 1 lattices: http://simul.iro.umontreal.ca/latbuilder/
* sobol with a small table? from marc b reynolds. https://github.com/Marc-B-Reynolds/Stand-alone-junk/blob/master/src/SFH/Sobol.h  includes stratified sobol sampling?
* irrational numbers with integers instead. https://twitter.com/marc_b_reynolds/status/1101608307217842176
* Stochastic Sampling in Computer Graphics (Pixar) http://www.cs.cmu.edu/afs/cs/academic/class/15462-s15/www/lec_slides/p51-cook.pdf
* correlated multi jittered sampling: https://graphics.pixar.com/library/MultiJitteredSampling/paper.pdf
* bilateral blue noise: https://www.liyiwei.org/papers/noise-siga13/
* multiclass blue noise sampling: https://www.liyiwei.org/papers/noise-sig10/
* a survey of blue noise sampling: http://archive.ymsc.tsinghua.edu.cn/pacm_download/38/276-2015_JCST_BNSurvey.pdf
* links at https://www.jasondavies.com/poisson-disc/
* find the electrostatic half toning paper
* Blue noise sampling using an N-body simulation-based method.  https://link.springer.com/article/10.1007/s00371-017-1382-9
* sample transformation zoo from http://www.realtimerendering.com/raytracinggems/

## Alan Specific TODOs
* progressive projective blue noise
* gather papers linked from progressive projective blue noise project
* James has a bluenoise type sampling he wants to contribute called dpp. Hit him up when you are ready to open things up!
* check out UTK (a sample comparison toolkit) for inspiration etc. https://utk-team.github.io/utk/
* check out these from Martin
 * "Aliasing-Free Blue Noise Sampling" https://kops.uni-konstanz.de/handle/123456789/20250
 * "Stair Blue Noise Sampling" https://www.researchgate.net/publication/308797027_Stair_Blue_Noise_Sampling
