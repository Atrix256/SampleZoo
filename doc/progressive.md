# Progressive vs Non Progressive Sequeneces

## Progressive Sequences

Progressive sequences are sequences that you can add more samples to as you desire without having to recreate everything from scratch.

For instance, random numbers are a progressive sequence.  If you have 5 random numbers but want a 6th, you can just add a 6th random number.

You can also remove items from the end of a progressive sequence without making it invalid.

If you have 5 random numbers but only want 3, you can just ignore the last 2 and you still have 3 random numbers.

Random numbers are special in that you could remove any value and it'd still be a valid random number sequence, but for most other progressive sequences, it's the end that you need to remove samples from.

A property of progressive sequences is that if you have N samples and haven't taken all samples yet, you'll still have "pretty good results" at every step of the way, due to subsets of the sequence 0..M also being valid sequences with the same basic sequence properties.

This is in contrast to non progressive sequences which will usually have very bad intermediary results until the very end.

## Non Progressive Sequences

Non progressive sequences are sequences where if you want to change the sample count in the sequence, you have to recreate them from scratch.

An example of a non progressive sequence is regular sampling.

Let's say you had 4 regular sampled points in [0,1) : 0, 0.25, 0.5, 0.75

If you want 5 regularly sampled points, you'd have to create it from scratch.  You can't just add another number to make it be the correct thing:  0, 0.2, 0.4, 0.6, 0.8.

Similarly, if you want 3 regularly sampled points, you can't just remove the last sample point to get the correct sequence: 0, 0.333, 0.666

## Sample Zoo Context

Some tests behave differently for progressive or non progressive sampling sequences, but the test documentation should explain the differences.

An example of where this comes up is in numerical integration, where you are graphing the sample count on the x axis and the integration error on the y axis.

If you are graphing 1 to N samples, for progressive sequences you can just generate an N sample sequence and graph the integration error at each step in the sequence.

For non progressive sequences, it gets a little more difficult though.  You need to generate a sequence for EVERY sample count 1 to N and calculate the sample count of that sequence.

The reason for this is because a non progressive sequence is almost always going to have A LOT of integration error in the beginning, regardless of how much error it gets to in the end.

If we don't do that, we aren't giving a fair apples to apples test between the sequences.  Nobody is going to use a non progressive sequence and expect it to keep up with a progressive sequence in integration error for intermediate samples.