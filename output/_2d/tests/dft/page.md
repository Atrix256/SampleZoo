# Discrete Fourier Transform
Source Code: [/src/families/_2d/tests/dft/](../../../../src/families/_2d/tests/dft/)

This is the same as the 1d DFT test, but in 2d.  The center of the image is 0hz.

[1D DFT Test](../../../_1d/tests/dft/page.md)  

Nothing special is done for randomized vs deterministic sequences, or progressive vs non progressive sequences.
# Test Results
 tests done:
* DFT
## DFT
### Blue Noise Sequences
#### BestCandidate (Progressive, Randomized)
![BestCandidate](../../../_2d/samples/blue_noise/DFT_BestCandidate.png)  
#### BestCandidate5 (Progressive, Randomized)
![BestCandidate5](../../../_2d/samples/blue_noise/DFT_BestCandidate5.png)  
#### BestCandidate10 (Progressive, Randomized)
![BestCandidate10](../../../_2d/samples/blue_noise/DFT_BestCandidate10.png)  
### Irrational Number Sampling
#### R2 (Progressive, Deterministic)
![R2](../../../_2d/samples/irrational_numbers/DFT_R2.png)  
#### R2Jittered (Progressive, Randomized)
![R2Jittered](../../../_2d/samples/irrational_numbers/DFT_R2Jittered.png)  
### Low Discrepancy Sequences
#### NRooks (Not Progressive, Randomized)
![NRooks](../../../_2d/samples/lds/DFT_NRooks.png)  
#### Hammersley (Not Progressive, Deterministic)
![Hammersley](../../../_2d/samples/lds/DFT_Hammersley.png)  
#### Hammersley_1Bit (Not Progressive, Deterministic)
![Hammersley_1Bit](../../../_2d/samples/lds/DFT_Hammersley_1Bit.png)  
#### Hammersley_2Bits (Not Progressive, Deterministic)
![Hammersley_2Bits](../../../_2d/samples/lds/DFT_Hammersley_2Bits.png)  
#### Sobol (Progressive, Deterministic)
![Sobol](../../../_2d/samples/lds/DFT_Sobol.png)  
#### Halton_2_3_Zero (Progressive, Deterministic)
![Halton_2_3_Zero](../../../_2d/samples/lds/DFT_Halton_2_3_Zero.png)  
#### Halton_2_3 (Progressive, Deterministic)
![Halton_2_3](../../../_2d/samples/lds/DFT_Halton_2_3.png)  
#### Halton_5_7 (Progressive, Deterministic)
![Halton_5_7](../../../_2d/samples/lds/DFT_Halton_5_7.png)  
#### Halton_13_9 (Progressive, Deterministic)
![Halton_13_9](../../../_2d/samples/lds/DFT_Halton_13_9.png)  
### Regular Sampling
#### Regular (Not Progressive, Deterministic)
![Regular](../../../_2d/samples/regular/DFT_Regular.png)  
#### RegularCentered (Not Progressive, Deterministic)
![RegularCentered](../../../_2d/samples/regular/DFT_RegularCentered.png)  
#### RegularCenteredOffset (Not Progressive, Deterministic)
![RegularCenteredOffset](../../../_2d/samples/regular/DFT_RegularCenteredOffset.png)  
#### RegularJittered (Not Progressive, Randomized)
![RegularJittered](../../../_2d/samples/regular/DFT_RegularJittered.png)  
### Uniform Random Number Sampling
#### UniformRandom (Progressive, Randomized)
![UniformRandom](../../../_2d/samples/uniform_random/DFT_UniformRandom.png)  
