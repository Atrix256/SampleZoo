# 1D Discrepancy Calculation

**namespace:** Tests::_1d::Discrepancy

Discrepancy is a real number given to a sampling sequence that describes how the points clump together or leave holes.

Discrepancy is calculated by finding the region with the largest difference between actual density of points and expected density if the points were evenly spaced.  The region with the largest difference may be either too dense, or too sparse.  That difference between actual and expected density in that region is the discrepancy.

In higher dimensions, the same process is followed with rectangular regions.  Sometimes this process will be simplified to just considering regions where one point is at the origin, which is an approximation of discrepancy calculated more quickly, called "Star Discrepancy", which is written as D*.

The discrepancy test has two functions available:
* CalculateDiscrepancy()
* CalculateDiscrepancyWrapAround()

CalculateDiscrepancy() calculates discrepancy assuming that 0 and 1 do not wrap around and are "hard walls".

The right most empty section that it checks for discrepancy is between the right most point and 1.0.

CalculateDiscrepancyWrapAround() calculates discrepancy assuming that 0 and 1 DO wrap around.

The right most empty section that it checks for discrepancy is between the right most point and the left most point, but wrapping around as if they were neighbors.

There are times when the things you are sampling wrap around, and other times when they don't, so it's important to know how your sampling sequence behaves in each situation.  These two discrepancy calculations can help you understand that better.

## Links

How to calculate discrepancy: https://math.stackexchange.com/questions/1681562/how-to-calculate-discrepancy-of-a-sequence

Wikipedia links:
* https://en.wikipedia.org/wiki/Equidistributed_sequence#Discrepancy
* https://en.wikipedia.org/wiki/Low-discrepancy_sequence#Definition_of_discrepancy

Star Discrepancy from Wolfram Math World: http://mathworld.wolfram.com/StarDiscrepancy.html

## Papers

"Discrepancy as a Quality Measure for Sample Distributions" by Peter Shirley (1991)  
http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.40.7922&rep=rep1&type=pdf


"Random-Edge Discrepancy of Supersampling Patterns" by David Dobkin & Don Mitchel (1993)  
https://pdfs.semanticscholar.org/5aec/55d3f5ed875a694cc3fb6a0cee42bd8cb92d.pdf


"Analysis of Forced Random Sampling" by Daniel Cornel  
http://drivenbynostalgia.com/files/DA.pdf
