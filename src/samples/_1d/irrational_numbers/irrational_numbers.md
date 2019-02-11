# Irrational Number Sampling

**namespace:** Samples::_1d::IrrationalNumbers

## Rational Numbers

Before we talk about using irrational numbers for generating sample points, let's talk about using rational numbers and start with the rational number 1/4.

To use rational numbers to make sample points, you just multiply the sample index by the rational number to get the sample point value.  Doing that, the first 4 samples you get are:

0, 1/4, 2/4, 3/4

That gave us regularly spaced sampling.

We could continue the series, but since we are sampling in [0,1), we use modulus to keep it in that range, and end up repeating the pattern over and over.  Here are 16 samples:

0, 1/4, 2/4, 3/4, 0, 1/4, 2/4, 3/4, 0, 1/4, 2/4, 3/4, 0, 1/4, 2/4, 3/4

Let's see what happens if we use 3/4.  Here are the first 4 samples:

0, 3/4, 2/4, 1/4

It's in a different pattern this time. It's still uniform sampling but the samples are in a different order.

If we take it to 16 samples, it still repeats every 4 samples though:

0, 3/4, 2/4, 1/4, 0, 3/4, 2/4, 1/4, 0, 3/4, 2/4, 1/4, 0, 3/4, 2/4, 1/4

Let's change it up a bit and use a value of 3/5.  Here are 16 samples:

0, 3/5, 1/5, 4/5, 2/5, 0, 3/5, 1/5, 4/5, 2/5, 0, 3/5, 1/5, 4/5, 2/5, 0

This sequence repeats every 5 samples.

Here are 16 samples using 2/3:

0, 2/3, 1/3, 0, 2/3, 1/3, 0, 2/3, 1/3, 0, 2/3, 1/3, 0, 2/3, 1/3, 0

That sequence repeats every 3 samples.

You might think that the pattern is that the denominator

TODO: 2/4!
