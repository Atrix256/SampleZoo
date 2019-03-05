# Discrete Fourier Transform
Source Code: [/src/families/_1d/tests/dft/](../../../../src/families/_1d/tests/dft/)

The discrete Fourier transform transforms a sampling sequence into frequency space.

## Technical Details

it does this by making a 1024x1 white image and placing black dots on the image where the sampling locations are.  it then runs the DFT on that.

For randomized sampling types, it does this test several times and reports the minimum, the maximum, and the average.

No windowing function is used (TODO: use a windowing function?)

## Less Technical

Viewing the samples in frequency space can help you understand some properties of the sampling sequence.

For instance, blue noise is missing low frequency content, so you can see for instance, how jittered grid looks compared to blue noise in frequency space.  They both are missing low frequency components, but look very different in frequency space despite this.

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
#### GoldenRatioZero (Progressive, Not Randomized)
![GoldenRatioZero](../../../_1d/samples/irrational_numbers/DFT_GoldenRatioZero.png)  
#### GoldenRatio (Progressive, Not Randomized)
![GoldenRatio](../../../_1d/samples/irrational_numbers/DFT_GoldenRatio.png)  
#### Pi (Progressive, Not Randomized)
![Pi](../../../_1d/samples/irrational_numbers/DFT_Pi.png)  
#### Sqrt2 (Progressive, Not Randomized)
![Sqrt2](../../../_1d/samples/irrational_numbers/DFT_Sqrt2.png)  
### Low Discrepancy Sequences
#### Sobol (Progressive, Not Randomized)
![Sobol](../../../_1d/samples/lds/DFT_Sobol.png)  
#### VanDerCorput2 (Progressive, Not Randomized)
![VanDerCorput2](../../../_1d/samples/lds/DFT_VanDerCorput2.png)  
#### VanDerCorput3 (Progressive, Not Randomized)
![VanDerCorput3](../../../_1d/samples/lds/DFT_VanDerCorput3.png)  
#### VanDerCorput5 (Progressive, Not Randomized)
![VanDerCorput5](../../../_1d/samples/lds/DFT_VanDerCorput5.png)  
### Regular Sampling
#### Regular (Not Progressive, Not Randomized)
![Regular](../../../_1d/samples/regular/DFT_Regular.png)  
#### RegularCentered (Not Progressive, Not Randomized)
![RegularCentered](../../../_1d/samples/regular/DFT_RegularCentered.png)  
#### RegularCenteredOffset (Not Progressive, Not Randomized)
![RegularCenteredOffset](../../../_1d/samples/regular/DFT_RegularCenteredOffset.png)  
#### RegularJittered (Not Progressive, Randomized)
![RegularJittered](../../../_1d/samples/regular/DFT_RegularJittered.png)  
### Uniform Random Number Sampling
#### UniformRandom (Progressive, Randomized)
![UniformRandom](../../../_1d/samples/uniform_random/DFT_UniformRandom.png)  
