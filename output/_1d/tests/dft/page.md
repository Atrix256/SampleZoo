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
#### BestCandidate
![BestCandidate](../../../_1d/samples/blue_noise/DFT_BestCandidate.png)  
#### BestCandidate5
![BestCandidate5](../../../_1d/samples/blue_noise/DFT_BestCandidate5.png)  
#### BestCandidate10
![BestCandidate10](../../../_1d/samples/blue_noise/DFT_BestCandidate10.png)  
#### BestCandidateRefined
![BestCandidateRefined](../../../_1d/samples/blue_noise/DFT_BestCandidateRefined.png)  
### Irrational Number Sampling
#### GoldenRatioZero
![GoldenRatioZero](../../../_1d/samples/irrational_numbers/DFT_GoldenRatioZero.png)  
#### GoldenRatio
![GoldenRatio](../../../_1d/samples/irrational_numbers/DFT_GoldenRatio.png)  
#### Pi
![Pi](../../../_1d/samples/irrational_numbers/DFT_Pi.png)  
#### Sqrt2
![Sqrt2](../../../_1d/samples/irrational_numbers/DFT_Sqrt2.png)  
### Low Discrepancy Sequences
#### Sobol
![Sobol](../../../_1d/samples/lds/DFT_Sobol.png)  
#### VanDerCorput2
![VanDerCorput2](../../../_1d/samples/lds/DFT_VanDerCorput2.png)  
#### VanDerCorput3
![VanDerCorput3](../../../_1d/samples/lds/DFT_VanDerCorput3.png)  
#### VanDerCorput5
![VanDerCorput5](../../../_1d/samples/lds/DFT_VanDerCorput5.png)  
### Regular Sampling
#### Regular
![Regular](../../../_1d/samples/regular/DFT_Regular.png)  
#### RegularCentered
![RegularCentered](../../../_1d/samples/regular/DFT_RegularCentered.png)  
#### RegularCenteredOffset
![RegularCenteredOffset](../../../_1d/samples/regular/DFT_RegularCenteredOffset.png)  
#### RegularJittered
![RegularJittered](../../../_1d/samples/regular/DFT_RegularJittered.png)  
### Uniform Random Number Sampling
#### UniformRandom
![UniformRandom](../../../_1d/samples/uniform_random/DFT_UniformRandom.png)  
