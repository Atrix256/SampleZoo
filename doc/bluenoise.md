# What is Blue Noise?

Blue noise are numbers that are randomized, but roughly evenly spaced, like the below.
![MakeNumberline_BestCandidate.png](../../../_1d/samples/uniform_random/MakeNumberline_UniformRandom.png)  

This is in contrast to regular old random number (white noise), which can clump together and leave empty holes.
![UniformRandom](../../../_1d/samples/uniform_random/MakeNumberline_UniformRandom.png)  

For a non graphics oriented explanation of why that's useful, check this out: https://blog.demofox.org/2018/01/30/what-the-heck-is-blue-noise/

For graphics, blue noise has some interesting properties:
* pro - gives the least aliasing
* pro - very easy on the eyes and looks a lot better than other noise patterns with the same amount of error
* pro - has good coverage over the sampling space, so has good starting error
* pro - it leaves high frequency noise, which is more easily removed with a less powerful low pass filter (aka blur) compared to other noise patterns
* pro - the error pattern it leaves is roughly evenly spaced.  It is as though error diffusion has happened, even though you don't have to explicitly do error diffusion (great for real time graphics)
* con - integrates at the same rate as white noise (slowly), even though it starts at a lower error.
* con - can be computationally expensive to generate

All this means that in general, if you can only afford a low sample count, and your result isn't going to converge all the way, you are best off using blue noise so that the remaining error is most pleasing to the eye and least noticeable.

If you have the benefit of a higher sample count, and your result is going to be allowed to fully converge, other sampling strategies are probably more appropriate.

Since I'm a real time graphics person, blue noise is very much my friend.  It allows me to get nice looking results with a very low sample count.

It's amazing what blue noise can accomplish at low sample counts, when doing apples to apples comparisons against other sampling strategies - most strikingly of all, compared to white noise which is jarring and hideous.

When i have concrete examples to show (when the dithering section is done, or if any shadows or AO type tests show up), I'll put them here.  In the meantime, here's a blog post that shows some examples: https://blog.demofox.org/2017/10/31/animating-noise-for-integration-over-time/

## Links:

Blue noise links from Mikkel Gjoel (https://twitter.com/pixelmager) of INSIDE fame
https://gist.github.com/pixelmager/5d25fa32987273b9608a2d2c6cc74bfa