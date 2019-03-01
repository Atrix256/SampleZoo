The discrete Fourier transform transforms a sampling sequence into frequency space.

## Technical Details

it does this by making a 1024x1 white image and placing black dots on the image where the sampling locations are.  it then runs the DFT on that.

For randomized sampling types, it does this test several times and reports the minimum, the maximum, and the average.

No windowing function is used (TODO: use a windowing function?)

## Less Technical

Viewing the samples in frequency space can help you understand some properties of the sampling sequence.

For instance, blue noise is missing low frequency content, so you can see for instance, how jittered grid looks compared to blue noise in frequency space.  They both are missing low frequency components, but look very different in frequency space despite this.
