# Regular Sampling
Source Code: [src/families/_2d/samples/regular/](../../../../src/families/_2d/samples/regular/)

The 2d regular sampling sequences are direct extensions of the 1d regular sampling sequences.

[1D Regular Sampling](../../../2d/output/_1d/samples/regular/page.md)  

It might be odd to see that RegularJittered has the lowest discrepancy of these sequences, but discrepancy gets a bit more complex in 2d.  Basically, those big empty rows and columns between samples in regular sampling contribute to making larger discrepancy for those sequences.  Adding random jitter causes those regions to get broken up.
# Test Results
 samples tested:
* Regular (Not Progressive, Deterministic)
* RegularCentered (Not Progressive, Deterministic)
* RegularCenteredOffset (Not Progressive, Deterministic)
* RegularJittered (Not Progressive, Randomized)
## Regular
### Discrete Fourier Transform
![Regular](../../../_2d/samples/regular/DFT_Regular.png)  
### Plot
![Regular](../../../_2d/samples/regular/MakePlot_Regular.png)  
## RegularCentered
### Discrete Fourier Transform
![RegularCentered](../../../_2d/samples/regular/DFT_RegularCentered.png)  
### Plot
![RegularCentered](../../../_2d/samples/regular/MakePlot_RegularCentered.png)  
## RegularCenteredOffset
### Discrete Fourier Transform
![RegularCenteredOffset](../../../_2d/samples/regular/DFT_RegularCenteredOffset.png)  
### Plot
![RegularCenteredOffset](../../../_2d/samples/regular/MakePlot_RegularCenteredOffset.png)  
## RegularJittered
### Discrete Fourier Transform
![RegularJittered](../../../_2d/samples/regular/DFT_RegularJittered.png)  
### Plot
![RegularJittered](../../../_2d/samples/regular/MakePlot_RegularJittered.png)  
## Discrepancy Test
![regular](../../../_2d/samples/regular/CalculateDiscrepancy.png)  
## Numerical Integration
### Disk
![regular](../../../_2d/samples/regular/Disk.png)  
### Triangle
![regular](../../../_2d/samples/regular/Triangle.png)  
### Step
![regular](../../../_2d/samples/regular/Step.png)  
### Gaussian
![regular](../../../_2d/samples/regular/Gaussian.png)  
### Bilinear
![regular](../../../_2d/samples/regular/Bilinear.png)  
