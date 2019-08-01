# Randomized vs Deterministic Sequeneces

Randomized sequences are sequences that use random numbers as part of generating sample points.

Deterministic sequences are sequences that don't.

As a high level concept, comparing regular sampling vs uniform random sampling (white noise), regular sampling has problems with aliasing while uniform random sampling trades the aliasing for noise, which is usually desired.

Because of this, randomized sequences will usually have less aliasing than their deterministic counterparts.

This can get murky though because ultimately, the "randomized sequences" are using deterministic, but chaotic, functions to generate the "random numbers".

Some sampling sequences can also be described as deterministic, but chaotic, which blurs the line between randomized and deterministic sequences.

To bring it back from philisophical debates about the nature of randomness, we can use these definitions:
* Randomized sequences will come up with different results each time a new sequence with the same number of points is generated.
* Deterministic sequences will always come up with the same results each time a new sequence with the same number of points is generated.

## Sample Zoo Context

Some tests behave differently for randomized vs deterministic sampling sequences, but the test documentation should explain the differences.

For instance, the 1d DFT test works differently for randomized and deterministic sequences.

For deterministic sequences, it makes a single sequence, DFTs it and shows the results.

For randomized sequences, it generates several sequences, DFTs them, and reports the maximum, the minimum, and the average.

It does this because any single instantiation of a randomized sequence isn't going to tell you much about what to expect from that sequence.  By gathering statistics of the sequence over several runs, you get a better idea of the sort of things to expect from the sequence.

Below you can see the DFT for 1d blue noise, which is randomized, and sobol which is not randomized (it is deterministic).

![RegularJittered](../output/_1d/samples/regular/DFT_RegularJittered.png)  
![RegularJittered](../output/_1d/samples/lds/DFT_Sobol.png)  

