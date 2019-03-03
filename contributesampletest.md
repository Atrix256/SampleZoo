# Contributing a Sequence or Test

Most people who want to contribute code to this project are going to want to contribute either a sampling sequence, or a test of sampling sequences.

This page is a step by step guide on how to do just that.  The process is meant to be as simple as possible to help contributors, but has a side effect of isolating these chunks of code into their own areas, making it easier for readers to find and take exactly what they want as quickly as possible.

The boilerplate code that interfaces with your sequence or test is auto generated to aid in this process.

In short, the steps are:
1. Make a subfolder with your code in it, in a specific location.
2. add a .lua file describing some properties of your sequence or test.
3. add a .md file explaining it and/or analyze test results.
4. run premake to generate code and documentation.
5. run the application to generate the test results.
6. Verify results, commit and push, make pull request.

## Make a Subfolder

First you need to make a subfolder in the appropriate location for your test or samples. The location depends on whether you are making a test or a sample sequence.

For samples: ./src/&lt;SampleFamily&gt;/samples/&lt;FolderName&gt;/  
For tests: ./src/&lt;SampleFamily&gt;/tests/&lt;FolderName&gt;/  
  
For instance, the 1d blue noise sample sequence code lives at ./src/families/_1d/samples/blue_noise/  
The 1d integration test code lives at ./src/families/_1d/tests/integration/  

The sub folder should be snake cased and should be representative of your test(s) or sample sequence(s), trying to prevent naming collisions or ambiguity as much as possible.

You may find that it makes sense to add your sample sequence or test code to an existing subfolder. We'll continue on as if that isn't the case, since it's more work when that isn't the case.

## Add a .md file

You should include a .md file that describes your test or sample sequence and does any analysis you want to do.  You can link to images if you want as part of your discussion.  You can also link to external links or papers that are relevant to the subject.

For samples, the file must be called samples.md and for tests, the file must be called tests.md.

For both samples and tests, this text is what ends up going above the automatically provided testing results.

## Add a .lua file

The .lua file describes your test(s) and sample sequence(s), controlling how both the code and documentation are generated.

for samples, the file must be called samples.lua and for tests, the file must be called tests.lua.  They have different options available in each file.

### samples.lua

```lua
sampleInfo = {
    CodeName="BlueNoise",
    ShortName="Blue Noise",
    LongName="Blue Noise Sequences",
    Description="Randomized sequences that have only high frequency content",
    Functions= {
        { name = "BestCandidate", progressive = true, randomized = true, cache = true },
        { name = "BestCandidate5", progressive = true, randomized = true, cache = true },
        { name = "BestCandidate10", progressive = true, randomized = true, cache = true },
        { name = "BestCandidateRefined", progressive = false, randomized = true, cache = true },
    },
}
```

* CodeName - The name used in code, for things like namespaces.
* ShortName - The name used in documentation when a shorter name is desired.
* LongName - the name used in documentation when a longer name is desired.
* Description - The description put next to the link to this content in the table of contents.
* Functions - one or more sampling functions each having:
  * name - this is used as a label for the samples in results, but also as the name of the function that implements it.
  * progressive - whether this sequence can have more samples added to it as needed (progressive) or if it needs to be rebuilt from scratch for different counts of samples (not progressive).
  * randomized - If the sequence is randomized, some tests will be run against the sequence multiple times to provide min, max, average, etc.
  * cache - Whether the samples should be cached on disk for subsequent runs.  This is useful for sequences that take a long time to create.  This should be false for most sequences, since it takes up a lot of space on disk to cache the sequences.

### tests.lua

```lua
testInfo = {
    CodeName="Discrepancy",
    ShortName="Discrepancy",
    LongName="Discrepancy Test",
    Description="Calculate metrics about actual point density compared to expected point density if the points were uniformly spaced.",
    Functions= {
        "CalculateDiscrepancy",
        "CalculateDiscrepancyWrapAround",
    },
    MakesIndividualImages = false,
    MakesSampleTypeImages = true,
    SamplePageShowsFunctionName = true,
}
```

* CodeName - The name used in code, for things like namespaces.
* ShortName - The name used in documentation when a shorter name is desired.
* LongName - the name used in documentation when a longer name is desired.
* Description - The description put next to the link to this content in the table of contents.
* Functions - an array of 1 or more test function names.  These are the names of functions that it expects you to provide implementations for.
* MakesIndividualImages - true if each sampling sequence has it's own image.  Used for generating documentation based on test results.
* MakesSampleTypeImages - true if each sampleing type has it's own image (eg LDS has multiple sampling sequences in it, but they all show on the same graph).  Used for generating documentation based on test results.
* SamplePageShowsFunctionName - If you have only one function in your test, you may not want to have it show the heading for the testing family as well as the testing function.  Set this to false to make it omit the testing function heading.

## Add your source code

You can have one or more cpp files and headers in that subfolder.  Many tests and sampling sequences only have a single cpp file.  The simpler the better for the readers.

You can copy the function signature of siblings, or wait til you get to the compile step and let the compiler tell you what the signature is by saying that the function is undefined.

## Run Premake

Run premake to generate the code (in ./build/codegen/) as well as documentation (./output/) for your test or sample sequence.  Note that the autogenerated documentation code will link to images even though they don't yet exist.

Your new documentation pages will also be linked to from the readme (front page) at this point etc.

## Run the code

Next, open up the solution and run the code.  This will call into your code and generate the images etc from your work.

## Verify Changes and Commit

You should make sure your changelist makes sense and that there are no extra files, stale files, or unexplained differences that don't relate to what you plan to submit.

You may need to commit and push and look at your documentation on github in your branch / fork.

Don't forget to add your name to the contributors page if you want your name there!

## Create a Pull Request

Next, create a pull request, and I'll get it.  I'll give it a look and let you know thumbs up or thumbs down with whatever recomendations there may be.

## Questions?

Ask away!  I'd love to do whatever I can to help get your contribution in.
