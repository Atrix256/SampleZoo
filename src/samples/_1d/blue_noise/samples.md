# Blue Noise Sampling

**namespace:** Samples::_1d::BlueNoise

Blue noise samples are randomized samples which are roughly evenly spaced.

It's called blue noise because if you do a DFT, there is primarily high frequency content.

This gives blue noise good coverage over a sampling space, just like regular sampling does,but because the points are still randomized, doesn't have problems with aliasing.

Blue noise has lower starting error than white noise in numerical integration but integrates at the same rate as white noise.

There are low discrepancy sequences that integrate faster than either blue or white noise, but when blue noise sampling hasn't yet fully converged, the noise pattern remaining is visually pleasing due to the error being nearly evenly spaced.

Because of this, blue noise is a good choice for low sample counts, but for higher sample counts, low discrepancy sequences or white noise can be better choices.

There are many ways to generate blue noise sample points, but there currently is only one way implemented:
* BestCandidate()

The BestCandidate() function uses Mitchell's best candidate algorithm to iteratively generate a number of random candidates (white noise) and choose the candidate which has the best blue noise properties.

This algorithm generates a progressive sequence which means that if you generate N sample points, any subset of those sample points starting at 0 is also blue noise.  Also, you can add more sample points to an existing set of sample points, without having to throw out all the points you already made.

This property can be very useful for when you don't know how many samples you want to take in advance.

Here are 16 blue noise sample points generated with Mitchell's best candidate algorithm.

![16 samples Regular](../../../../output/samples/_1d/blue_noise/BestCandidate.png)

# Links

https://blog.demofox.org/2017/10/20/generating-blue-noise-sample-points-with-mitchells-best-candidate-algorithm/ - Generating Blue Noise Sample Points With Mitchell’s Best Candidate Algorithm  
