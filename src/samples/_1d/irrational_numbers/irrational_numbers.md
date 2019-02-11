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

You might think that the pattern is that the denominator determines how long it takes for the pattern to repeat, but here's 16 samples of 2/4:

0, 2/4, 0, 2/4, 0, 2/4, 0, 2/4, 0, 2/4, 0, 2/4, 0, 2/4, 0, 2/4

That repeats every 2 samples!

If you reduce the fraction 2/4 you get 1/2, which explains why we saw it repeating every 2 samples.

So, the rule is, if you have a reduced fraction, the denominator is what determines how long it takes for the sequence to repeat.

A little more formally, if you have two numbers A and B, and they are coprime (they don't have any common divisors except 1), then using the rational number A/B to generate a sequence will repeat after B steps.

The formula for calculating sample I is this:  (I * A / B) mod 1

### Quick Tangent - Fast and Cheap Shuffles

If you ever find yourself in the need of a fast and cheap shuffle, an offshoot of this technique might be for you.

How it works is if the number of items you need to shuffle is N, you take any coprime number to that M as your "shuffle seed".  Choosing different values of M will result in different shuffles.

To get item I in the shuffle you just calculate this:  (I * M) mod N

The resulting number is the index to use in the array at step I, so an upside is that you don't actually need to do a shuffle, or stored a shuffled list.

A downside is that not all shuffle orders are always possible, and are limited by how many possible M values there are (which is less than N), but this can work well in a pinch.

This can also be used as a "random number generator" but i put it in quotes because it's so low quality, it isn't very often useful even in game development, which has much lower needs than cryptographic random numbers.  Definitely don't use this as a white noise generator for monte carlo integration or anything like that!!

## Irrational Numbers

Irrational numbers are numbers that can't be written as fractions (aka ratios, that's where the "rational" part of the word comes from).

Since the denominator of the reduced fraction is what defines how long the sequence takes to repeat, and irrational numbers have no denominator, that means they don't repeat - which is true.

The formula for using irrational numbers is essentially the same as when using rational numbers.  If X is the irrational number and you want to calculate sample I, it's: (I * X) mod 1

That can make for a great number sequence like the below, which uses the square root of two (which is an irrational number) in the same formula as before for 16 samples:

![16 samples sqrt2](../../../../output/samples/_1d/irrational_numbers/sqrt2.png)

Just because a number is irrational doesn't make it a good choice though.  Here is 16 samples of pi:

![16 samples pi](../../../../output/samples/_1d/irrational_numbers/pi.png)

TODO: phi
