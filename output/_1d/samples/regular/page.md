# Regular Sampling
Source Code: [src/families/_1d/samples/regular/](../../../../src/families/_1d/samples/regular/)

Regular sampling is also known as uniformly spaced sampling, regular grid sampling, it could be called "periodic sampling", and has some other names as well.

This sampling strategy takes samples at even spaces which can show good convergence, but comes at the cost of aliasing.

Randomized sampling is often favored over regularly spaced samples to get rid of aliasing problems, at the cost of gaining noise.

Regular spaced samples are the lowest discrepancy sampling you can do in 1D, but you actually want some discrepancy for best results, so "low discrepancy sequences" are actually better even though they have higher discrepancy than regular sampling.

See the page about the 1d discrepancy calculation test to learn more about discrepancy.

These are the regular sampling strategies supplied:
* Regular()
* RegularCentered()
* RegularCenteredOffset()
* RegularJittered()

## Regular()

This does evenly spaced sampling starting at 0 and going to (N-1)/N, in step sizes of 1/N.

If N is 4, the sampling pattern is:  0, 1/4, 2/4, 3/4.

A problem here is that if you take the average of those numbers, you get 0.375, instead of 0.5 like you might expect.  That can affect the quality of the sampling.

(Note: if what you are sampling wraps around and gives 0 and 1 the same meaning, this isn't a problem. There is no "true center" of the data, and you coud slide things around for 0.375 to be where 0.5 is. That is in fact effectively what is done in RegularCenteredOffset()!)

![Regular](../../../_1d/samples/regular/MakeNumberline_Regular.png)  

At 16 samples, these samples have a discrepancy, and torroidal discrepancy of 0.0625 which is 1/16.

## RegularCentered()

This does evenly spaced sampling, starting at 0 and going to 1, in step sizes of 1/(N-1).

If N is 4, the sampling pattern is: 0, 1/3, 2/3, 1.

Averaging those values gives 0.5.

If you are sampling something that gives the same meaning to 0 and 1 (when it wraps around, or is toroidal), a problem with this sequence is that it has 2 samples in the same location (the 0 and 1 are the same), so weights that sample location more highly (adding bias), and also gives less sampling coverage over the sampling domain, which affects the quality of the sampling.

![RegularCentered](../../../_1d/samples/regular/MakeNumberline_RegularCentered.png)  

At 16 samples have a discrepancy, and torroidal discrepancy of 0.125, which is 1/8. That is double the discrepancy of Regular()!

## RegularCenteredOffset()

This is the same pattern as Regular, but adds 1/(2n) to each sample position.

If N is 4, the sampling pattern is: 1/8, 3/8, 5/8, 7/8.

Averaging those values gives 0.5.

If you are sampling something that gives the same meanting to 0 and 1, this sequence has N distinct sample locations and the distance between all of the samples is a constant 1/N.

![RegularCenteredOffset](../../../_1d/samples/regular/MakeNumberline_RegularCenteredOffset.png)  

At 16 samples have a discrepancy, and torroidal discrepancy of 0.0625 which is 1/16.

This sampling strategy is seemingly the best of the three because it works well for both the wrap around and non wrap around cases, and is tied for lowest discrepancy.

## RegularJittered()

This is the same as Regular(), but each sample has a random number added to it that is between 0 and 1/N.  This is the same as cutting the numberline into N buckets, and putting a sample at a random location in each bucket.

This technique was invented by Pixar and as I understand it was patented until recently when the patent expired.

This technique, and higher dimensional versions of it called jittered grid, give a frequency spectrum more like blue noise than either regular sampling or uniform random (white noise), which means that it is better at not having aliasing problems, but it still has good coverage over the sampling space.

From the tests you can see that jittered grid has almost as high discrepancy as RegularCentered() but not quite.  In the integration tests you can't see a difference in integration error, although if we had some sort of visual example, you would see that it had less aliasing problems (at the cost of introducing noise to the result).

![RegularJittered](../../../_1d/samples/regular/MakeNumberline_RegularJittered.png)  

This is also known as stratified sampling.

# Test Results
 samples tested:
* Regular (Not Progressive, Not Randomized)
* RegularCentered (Not Progressive, Not Randomized)
* RegularCenteredOffset (Not Progressive, Not Randomized)
* RegularJittered (Not Progressive, Randomized)
## Regular
### Discrete Fourier Transform
![Regular](../../../_1d/samples/regular/DFT_Regular.png)  
### Numberline
![Regular](../../../_1d/samples/regular/MakeNumberline_Regular.png)  
## RegularCentered
### Discrete Fourier Transform
![RegularCentered](../../../_1d/samples/regular/DFT_RegularCentered.png)  
### Numberline
![RegularCentered](../../../_1d/samples/regular/MakeNumberline_RegularCentered.png)  
## RegularCenteredOffset
### Discrete Fourier Transform
![RegularCenteredOffset](../../../_1d/samples/regular/DFT_RegularCenteredOffset.png)  
### Numberline
![RegularCenteredOffset](../../../_1d/samples/regular/MakeNumberline_RegularCenteredOffset.png)  
## RegularJittered
### Discrete Fourier Transform
![RegularJittered](../../../_1d/samples/regular/DFT_RegularJittered.png)  
### Numberline
![RegularJittered](../../../_1d/samples/regular/MakeNumberline_RegularJittered.png)  
## Discrepancy Test
![regular](../../../_1d/samples/regular/CalculateDiscrepancy.png)  
## Numerical Integration
### Linear
![regular](../../../_1d/samples/regular/Linear.png)  
### Step
![regular](../../../_1d/samples/regular/Step.png)  
### Exp
![regular](../../../_1d/samples/regular/Exp.png)  
### Quadratic
![regular](../../../_1d/samples/regular/Quadratic.png)  
