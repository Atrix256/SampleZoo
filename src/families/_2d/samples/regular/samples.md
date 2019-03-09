The 2d regular sampling sequences are direct extensions of the 1d regular sampling sequences.

[1D Regular Sampling](../../../_1d/samples/regular/page.md)  

It might be odd to see that RegularJittered has the lowest discrepancy of these sequences, but discrepancy gets a bit more complex in 2d.  Basically, those big empty rows and columns between samples in regular sampling contribute to making larger discrepancy for those sequences.  Adding random jitter causes those regions to get broken up.

The lower discrepancy means that it also does better at integration.
