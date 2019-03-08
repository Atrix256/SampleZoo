# Mitchell's Best Candidate Algorithm

This algorithm iteratively generates a number of random candidates (white noise) and chooses the candidate which has the best blue noise properties (largest distance from it's nearest neighbor).

The paper that describes the algorithm originally (in papers section below) says that that the number of candidates should scale up with the number of points you already have to keep consistent frequency content at different sample counts.  I've found that keeping the multiplier at 1.0 seems to be best.

This algorithm generates a progressive sequence which means that if you generate N sample points, any subset of those sample points starting at 0 is also blue noise.  Also, you can add more sample points to an existing set of sample points, without having to throw out all the points you already made.

This property can be very useful for when you don't know how many samples you want to take in advance, or if you are using it for rendering, being able to preview the image as it renders and see something more representative of the final image.  With a non progressive sequence used in rendering, the image looks very bad until the end.

## Links

https://blog.demofox.org/2017/10/20/generating-blue-noise-sample-points-with-mitchells-best-candidate-algorithm/ - Generating Blue Noise Sample Points With Mitchell’s Best Candidate Algorithm  

## Papers

http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.556.445&rep=rep1&type=pdf - "Spectrally Optimal Sampling for Distribution Ray Tracing" by Don P. Mitchell 1991