Blue noise samples are randomized samples which are roughly evenly spaced.

More details:
[What is Blue Noise?](../../../../doc/bluenoise.md)  

There are many ways to generate 1d blue noise sample points, but there currently is only one way implemented:
* [Mitchell's Best Candidate](../../../../doc/bestcandidate.md)  

There are three variations, each using a different multiplier for the number of candidates generated compared to how many blue noise samples there already are: 1, 5 and 10.