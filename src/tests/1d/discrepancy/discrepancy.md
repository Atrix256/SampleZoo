# 1D Discrepancy Calculation

**namespace:** Tests::_1d::Discrepancy

Discrepancy is a real number given to a sampling sequence that describes how the points clump together or leave holes.

Discrepancy is calculated by finding the region with the largest difference between actual density of points and expected density if the points were evenly spaced.  That difference between actual and expected density is the discrepancy.

Discrepancy is able to be calculated exactly in 1D, but it gets a lot harder in higher dimensions, because you have to consider all possible regions of space, and every shape of those regions.  In higher dimensions you'll see approximations of discrepancy, such as "Star Discrepancy" which is written as D*.

The discrepancy test has two functions available:
* CalculateDiscrepancy()
* CalculateDiscrepancyWrapAround()

## CalculateDiscrepancy

## CalculateDiscrepancyWrapAround

## Links

Some links on discrepancy:

How to calculate discrepancy: https://math.stackexchange.com/questions/1681562/how-to-calculate-discrepancy-of-a-sequence
Wikipedia links:
https://en.wikipedia.org/wiki/Equidistributed_sequence#Discrepancy
https://en.wikipedia.org/wiki/Low-discrepancy_sequence#Definition_of_discrepancy

Star Discrepancy from Wolfram Math World: http://mathworld.wolfram.com/StarDiscrepancy.html

TODO: Finish this!
