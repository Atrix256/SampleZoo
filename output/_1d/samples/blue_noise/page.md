# Blue Noise Sequences
Source Code: [src/families/_1d/samples/blue_noise/](../../../../src/families/_1d/samples/blue_noise/)

Blue noise samples are randomized samples which are roughly evenly spaced.

More info about blue noise:
![Blue Noise](../../../../doc/bluenoise.md)  

There are many ways to generate 1d blue noise sample points, but there currently is only one way implemented:
* [Mitchell's Best Candidate](../../../../doc/bestcandidate.md)  

# Comparison vs Other Sequences

![BestCandidateRefined](../../../_1d/samples/blue_noise/Doc_CalculateDiscrepancy.png)  
![BestCandidateRefined](../../../_1d/samples/blue_noise/Doc_Quadratic.png)  

# Test Results
 samples tested:
* BestCandidate (Progressive, Randomized)
* BestCandidate5 (Progressive, Randomized)
* BestCandidate10 (Progressive, Randomized)
## BestCandidate
### Discrete Fourier Transform
![BestCandidate](../../../_1d/samples/blue_noise/DFT_BestCandidate.png)  
### Numberline
![BestCandidate](../../../_1d/samples/blue_noise/MakeNumberline_BestCandidate.png)  
## BestCandidate5
### Discrete Fourier Transform
![BestCandidate5](../../../_1d/samples/blue_noise/DFT_BestCandidate5.png)  
### Numberline
![BestCandidate5](../../../_1d/samples/blue_noise/MakeNumberline_BestCandidate5.png)  
## BestCandidate10
### Discrete Fourier Transform
![BestCandidate10](../../../_1d/samples/blue_noise/DFT_BestCandidate10.png)  
### Numberline
![BestCandidate10](../../../_1d/samples/blue_noise/MakeNumberline_BestCandidate10.png)  
## Discrepancy Test
![blue_noise](../../../_1d/samples/blue_noise/CalculateDiscrepancy.png)  
## Numerical Integration
### Linear
![blue_noise](../../../_1d/samples/blue_noise/Linear.png)  
### Step
![blue_noise](../../../_1d/samples/blue_noise/Step.png)  
### Exp
![blue_noise](../../../_1d/samples/blue_noise/Exp.png)  
### Quadratic
![blue_noise](../../../_1d/samples/blue_noise/Quadratic.png)  
