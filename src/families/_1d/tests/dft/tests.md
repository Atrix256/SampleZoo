The discrete Fourier transform transforms a sampling sequence into frequency space.

The test generates 128 samples and places them as black dots in a 1024x1 white image, and does a DFT of that image.

For randomized sampling types, it does this test several times and reports the minimum, the maximum, and the average.  Deterministic sampling sequences just do a single run.

There is no difference in this test for progressive vs non progressive sequences since it only ever generates a single 128 length sequence per sequence type.

No windowing function is used, but in some cases (non torroidal sampling!), a windowing function may make sense.
