# Low Discrepancy Sequences
Source Code: [src/families/_2d/samples/lds/](../../../../src/families/_2d/samples/lds/)

This extends the concept of low discrepancy numbers from 1d to 2d.

Check out the 1d low discrepancy sequence page for an explanation of the basic ideas:
[1D Low Discrepancy Sequences](../../../2d/output/_1d/samples/lds/page.md)  

## N-Rooks

N-Rooks is a sampling pattern where you treat an NxN image as if it were a chess board.  Every sampling position is a rook that could move horizontally or vertically, and should be placed such that none of these rooks could capture / "see" any of the other rooks.

In other words, every column has a single sample point in it, and every row has a single sample point in it.

An easy way to do this is to start by having a diagonal line of the rooks like (0,0) (1,1) (2,2) ... (N-1, N1), and then randomly shuffling the rows.

While this sampling pattern is randomized pretty heavily using white noise, the 1d projections of this pattern on the X and Y axis have no overlap and are a shuffle, making it better than white noise and also pretty easy to generate.




TODO: finish this page!
# Test Results
 samples tested:
* NRooks (Not Progressive, Randomized)
* Sobol (Progressive, Deterministic)
* Halton_2_3_Zero (Progressive, Deterministic)
* Halton_2_3 (Progressive, Deterministic)
* Halton_5_7 (Progressive, Deterministic)
* Halton_13_9 (Progressive, Deterministic)
## NRooks
### Discrete Fourier Transform
![NRooks](../../../_2d/samples/lds/DFT_NRooks.png)  
### Plot
![NRooks](../../../_2d/samples/lds/MakePlot_NRooks.png)  
## Sobol
### Discrete Fourier Transform
![Sobol](../../../_2d/samples/lds/DFT_Sobol.png)  
### Plot
![Sobol](../../../_2d/samples/lds/MakePlot_Sobol.png)  
## Halton_2_3_Zero
### Discrete Fourier Transform
![Halton_2_3_Zero](../../../_2d/samples/lds/DFT_Halton_2_3_Zero.png)  
### Plot
![Halton_2_3_Zero](../../../_2d/samples/lds/MakePlot_Halton_2_3_Zero.png)  
## Halton_2_3
### Discrete Fourier Transform
![Halton_2_3](../../../_2d/samples/lds/DFT_Halton_2_3.png)  
### Plot
![Halton_2_3](../../../_2d/samples/lds/MakePlot_Halton_2_3.png)  
## Halton_5_7
### Discrete Fourier Transform
![Halton_5_7](../../../_2d/samples/lds/DFT_Halton_5_7.png)  
### Plot
![Halton_5_7](../../../_2d/samples/lds/MakePlot_Halton_5_7.png)  
## Halton_13_9
### Discrete Fourier Transform
![Halton_13_9](../../../_2d/samples/lds/DFT_Halton_13_9.png)  
### Plot
![Halton_13_9](../../../_2d/samples/lds/MakePlot_Halton_13_9.png)  
## Discrepancy Test
![lds](../../../_2d/samples/lds/CalculateDiscrepancy.png)  
## Numerical Integration
### Disk
![lds](../../../_2d/samples/lds/Disk.png)  
### Triangle
![lds](../../../_2d/samples/lds/Triangle.png)  
### Step
![lds](../../../_2d/samples/lds/Step.png)  
### Gaussian
![lds](../../../_2d/samples/lds/Gaussian.png)  
### Bilinear
![lds](../../../_2d/samples/lds/Bilinear.png)  
