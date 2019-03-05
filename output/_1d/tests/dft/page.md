# Discrete Fourier Transform
Source Code: [/src/families/_1d/tests/dft/](../../../../src/families/_1d/tests/dft/)

The discrete Fourier transform transforms a sampling sequence into frequency space.

The test generates 128 samples and places them as black dots in a 1024x1 white image, and does a DFT of that image.

For randomized sampling types, it does this test several times and reports the minimum, the maximum, and the average.  Deterministic sampling sequences just do a single run.

There is no difference in this test for progressive vs non progressive sequences since it only ever generates a single 128 length sequence per sequence type.

No windowing function is used (TODO: use a windowing function?)

# Test Results
 tests done:
* DFT
## DFT
### Blue Noise Sequences
#### BestCandidate (Progressive, Randomized)
![BestCandidate](../../../_1d/samples/blue_noise/DFT_BestCandidate.png)  
#### BestCandidate5 (Progressive, Randomized)
![BestCandidate5](../../../_1d/samples/blue_noise/DFT_BestCandidate5.png)  
#### BestCandidate10 (Progressive, Randomized)
![BestCandidate10](../../../_1d/samples/blue_noise/DFT_BestCandidate10.png)  
#### BestCandidateRefined (Not Progressive, Randomized)
![BestCandidateRefined](../../../_1d/samples/blue_noise/DFT_BestCandidateRefined.png)  
### Irrational Number Sampling
#### GoldenRatioZero (Progressive, Deterministic)
![GoldenRatioZero](../../../_1d/samples/irrational_numbers/DFT_GoldenRatioZero.png)  
#### GoldenRatio (Progressive, Deterministic)
![GoldenRatio](../../../_1d/samples/irrational_numbers/DFT_GoldenRatio.png)  
#### Pi (Progressive, Deterministic)
![Pi](../../../_1d/samples/irrational_numbers/DFT_Pi.png)  
#### Sqrt2 (Progressive, Deterministic)
![Sqrt2](../../../_1d/samples/irrational_numbers/DFT_Sqrt2.png)  
### Low Discrepancy Sequences
#### Sobol (Progressive, Deterministic)
![Sobol](../../../_1d/samples/lds/DFT_Sobol.png)  
#### VanDerCorput2 (Progressive, Deterministic)
![VanDerCorput2](../../../_1d/samples/lds/DFT_VanDerCorput2.png)  
#### VanDerCorput3 (Progressive, Deterministic)
![VanDerCorput3](../../../_1d/samples/lds/DFT_VanDerCorput3.png)  
#### VanDerCorput5 (Progressive, Deterministic)
![VanDerCorput5](../../../_1d/samples/lds/DFT_VanDerCorput5.png)  
### Regular Sampling
#### Regular (Not Progressive, Deterministic)
![Regular](../../../_1d/samples/regular/DFT_Regular.png)  
#### RegularCentered (Not Progressive, Deterministic)
![RegularCentered](../../../_1d/samples/regular/DFT_RegularCentered.png)  
#### RegularCenteredOffset (Not Progressive, Deterministic)
![RegularCenteredOffset](../../../_1d/samples/regular/DFT_RegularCenteredOffset.png)  
#### RegularJittered (Not Progressive, Randomized)
![RegularJittered](../../../_1d/samples/regular/DFT_RegularJittered.png)  
### Uniform Random Number Sampling
#### UniformRandom (Progressive, Randomized)
![UniformRandom](../../../_1d/samples/uniform_random/DFT_UniformRandom.png)  
