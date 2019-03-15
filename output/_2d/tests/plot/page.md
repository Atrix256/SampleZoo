# Plot
Source Code: [/src/families/_2d/tests/plot/](../../../../src/families/_2d/tests/plot/)

Plotting 2d sample points is the 2d equivelant of the 1d numberline tests.

[1D Regular Sampling](../../../_1d/tests/numberline/page.md)  

A difference from 1d however, is that we also project the points to the X and Y axis.

Several modern research papers say and show that sampling sequences that are "still good" (for instance, low discrepancy) when projected to an axis outperform sequences that don't.  This test showing those projections let you see how well the sequences project to those lower subspaces.

For some intuition about why this is true, imagine that you are integrating over a square region of pixels that has a vertical line in it, where everything to the right is black, and everything to the left is white.

When you use a 2d sampling location to sample this region, the y axis doesn't matter. Whatever you change the y axis to, as long as you leave x alone, you'll get the same value.

Because of this, it reduces the sampling / integration problem to 1d, on the x axis specifically.

That means that the quality of the sampling sequence in this situation is going to be based entirely on how good the x axis projection of the sampling sequence can do in 1d.

This might sound far fetched, but imagine trying to integrate some soft shadows for a vertical building.  You are likely going to hit this exact problem.

Thinking about this, you might wonder (like i do) why the x and y axis is so special.  Wouldn't you want something that projects as well as possible on all random axes?  I definitely think so but have not yet seen any research papers talking about this.

## Papers

http://resources.mpi-inf.mpg.de/ProjectiveBlueNoise/ - "Projective Blue-Noise Sampling " from 2015
# Test Results
 tests done:
* MakePlot
## MakePlot
### Blue Noise Sequences
#### BestCandidate (Progressive, Randomized)
![BestCandidate](../../../_2d/samples/blue_noise/MakePlot_BestCandidate.png)  
#### BestCandidate5 (Progressive, Randomized)
![BestCandidate5](../../../_2d/samples/blue_noise/MakePlot_BestCandidate5.png)  
#### BestCandidate10 (Progressive, Randomized)
![BestCandidate10](../../../_2d/samples/blue_noise/MakePlot_BestCandidate10.png)  
### Irrational Number Sampling
#### R2 (Progressive, Deterministic)
![R2](../../../_2d/samples/irrational_numbers/MakePlot_R2.png)  
#### R2Jittered (Progressive, Randomized)
![R2Jittered](../../../_2d/samples/irrational_numbers/MakePlot_R2Jittered.png)  
### Low Discrepancy Sequences
#### NRooks (Not Progressive, Randomized)
![NRooks](../../../_2d/samples/lds/MakePlot_NRooks.png)  
#### Hammersley2NoOffset (Not Progressive, Deterministic)
![Hammersley2NoOffset](../../../_2d/samples/lds/MakePlot_Hammersley2NoOffset.png)  
#### Hammersley2 (Not Progressive, Deterministic)
![Hammersley2](../../../_2d/samples/lds/MakePlot_Hammersley2.png)  
#### Hammersley3 (Not Progressive, Deterministic)
![Hammersley3](../../../_2d/samples/lds/MakePlot_Hammersley3.png)  
#### Hammersley5 (Not Progressive, Deterministic)
![Hammersley5](../../../_2d/samples/lds/MakePlot_Hammersley5.png)  
#### Hammersley2_1Bit (Not Progressive, Deterministic)
![Hammersley2_1Bit](../../../_2d/samples/lds/MakePlot_Hammersley2_1Bit.png)  
#### Hammersley2_2Bit (Not Progressive, Deterministic)
![Hammersley2_2Bit](../../../_2d/samples/lds/MakePlot_Hammersley2_2Bit.png)  
#### Hammersley2_3Bit (Not Progressive, Deterministic)
![Hammersley2_3Bit](../../../_2d/samples/lds/MakePlot_Hammersley2_3Bit.png)  
#### Hammersley2_4Bit (Not Progressive, Deterministic)
![Hammersley2_4Bit](../../../_2d/samples/lds/MakePlot_Hammersley2_4Bit.png)  
#### Sobol (Progressive, Deterministic)
![Sobol](../../../_2d/samples/lds/MakePlot_Sobol.png)  
#### Halton_2_3_Zero (Progressive, Deterministic)
![Halton_2_3_Zero](../../../_2d/samples/lds/MakePlot_Halton_2_3_Zero.png)  
#### Halton_2_3 (Progressive, Deterministic)
![Halton_2_3](../../../_2d/samples/lds/MakePlot_Halton_2_3.png)  
#### Halton_5_7 (Progressive, Deterministic)
![Halton_5_7](../../../_2d/samples/lds/MakePlot_Halton_5_7.png)  
#### Halton_13_9 (Progressive, Deterministic)
![Halton_13_9](../../../_2d/samples/lds/MakePlot_Halton_13_9.png)  
### Regular Sampling
#### Regular (Not Progressive, Deterministic)
![Regular](../../../_2d/samples/regular/MakePlot_Regular.png)  
#### RegularCentered (Not Progressive, Deterministic)
![RegularCentered](../../../_2d/samples/regular/MakePlot_RegularCentered.png)  
#### RegularCenteredOffset (Not Progressive, Deterministic)
![RegularCenteredOffset](../../../_2d/samples/regular/MakePlot_RegularCenteredOffset.png)  
#### RegularJittered (Not Progressive, Randomized)
![RegularJittered](../../../_2d/samples/regular/MakePlot_RegularJittered.png)  
### Uniform Random Number Sampling
#### UniformRandom (Progressive, Randomized)
![UniformRandom](../../../_2d/samples/uniform_random/MakePlot_UniformRandom.png)  
