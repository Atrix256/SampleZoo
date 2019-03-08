Blue noise samples are randomized but roughly evenly spaced.

More details: [What is Blue Noise?](../../../../doc/bluenoise.md)  

There are many ways to generate 1d blue noise sample points, but there currently is only one way implemented:
* [Mitchell's Best Candidate](../../../../doc/bestcandidate.md)  

There are three variations, each using a different multiplier for the number of candidates generated compared to how many blue noise samples there already are: 1, 5 and 10.

# Comparison vs Other Sequences

![BestCandidateRefined](../../../_1d/samples/blue_noise/Doc_CalculateDiscrepancy.png)  
![BestCandidateRefined](../../../_1d/samples/blue_noise/Doc_Quadratic.png)  
