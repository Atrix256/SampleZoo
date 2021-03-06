# Progressive and Open Sequences

## Progressive Sequences

Progressive sequences are sequences that keep their desirable properties when using a subset of the entire sequence.

For instance, random numbers are a progressive sequence.  If you have 5 random numbers but only want 3, you can just throw away the last 2 and you still have 3 perfectly good random numbers.

For most progressive sequences, it's the end that you need to remove samples from to keep the sequence valid, but some sequences have less restrictive rules.  Random numbers are trivially progressive for any subset.  Sobol is progressive for any power of two region.

Non progressive sequences are sequences where if you want to change the sample count in the sequence, you have to recreate them from scratch.

An example of a non progressive sequence is regular sampling.

Let's say you had 4 regular sampled points in [0,1) : 0, 0.25, 0.5, 0.75

If you only wanted to use 3 of those samples, it wouldn't be regularly sampled points anymore.  It would be 0, 0.25, 0.5 instead of 0, 0.333, 0.666.

## Open Sequences

Open sequences are sequences that are unbounded in size.

Random numbers are an open sequence: you can add more random numbers to the end, and the sequence as a whole is still perfectly random.

Regularly sampled points are not open though.  If you have 4 points: 0, 0.25, 0.5, 0.75, you can't just add a 5th point, you have to remake the sequence from scratch for 5 samples to get 0, 0.2, 0.4, 0.6, 0.8.

Van Der Corput is an example of a non trivial open sequence.  You can keep adding more and more Van Der Corput points to infinity.

All open sequences are progressive, but not all progressive sequences are open.

As a more complex example, you could use CCVD to make 512 blue noise sample points, and use techniques from the void and cluster algorithm to make those sample points progressive, but you can't add any more new points after the fact without re-running the relaxation algorithm and invalidating all the existing points.

## Sets vs Sequences

Sometimes people will refer to samples as sets or sequences.

Sequences have an ordering while sets do not.

## Sample Zoo Context

Some tests behave differently for progressive or non progressive sampling sequences, but the test documentation should explain the differences.

An example of where this comes up is in numerical integration, where you are graphing the sample count on the x axis and the integration error on the y axis.

If you are graphing 1 to N samples, for progressive sequences you can just generate an N sample sequence and graph the integration error at each step in the sequence.

For non progressive sequences, it gets a little more difficult though.  You need to generate a sequence for EVERY sample count 1 to N and calculate the sample count of that sequence.

The reason for this is because a non progressive sequence is almost always going to have A LOT of integration error in the beginning, regardless of how much error it gets to in the end.

If we don't do that, we aren't giving a fair apples to apples test between the sequences.  Nobody is going to use a non progressive sequence and expect it to keep up with a progressive sequence in integration error for intermediate samples.

Below you can see the numberline for the golden ratio sequence, which is progressive. Note how each sample count contains all previous samples.  Below that is a regular sampling sequence which is not progressive. Note how each sample count DOES NOT contain all previous samples

![RegularJittered](../output/_1d/samples/irrational_numbers/MakeNumberline_GoldenRatio.png)  
![RegularJittered](../output/_1d/samples/regular/MakeNumberline_RegularCenteredOffset.png)  