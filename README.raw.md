![SampleZoo](SampleZoo.jpg)

# Table of Contents

* [Progressive vs Non Progressive Sequeneces](./doc/progressive.md)
* [Randomized vs Non Randomized Sequeneces](./doc/randomized.md)
* [Discrete Fourier Transform (DFT) Testing](./doc/dft.md)

TOCTOC

# SampleZoo
Simple copy/paste-able implementations of sampling patterns, with objective and subjective tests to compare them, along with understandable explanations.

Created by Alan Wolfe
email: alan.wolfe@gmail.com
twitter: https://twitter.com/Atrix256

Building and running this code: [building](building.md)

Everything in this repository is under the [MIT License](LICENSE) unless otherwise stated in the source file.

Full list of contributors here: [credits](credits.md)

Information on how to contribute to this project: [contributing](contributing.md)

# Why Does This Exist??

My interest in sampling patterns is mainly for use in numerical integration techniques in real time graphics.  In that situation, you usually want a sequence that will converge with as few samples as possible, and give a pleasing error pattern when it hasn't fully converged.

This stuff is surprisingly nuanced, and new sampling techniques come out every year as researchers continue to push the envelope.

It can be hard to find implementations for some sampling patterns, especially if they are newly published.  Furthermore, each sampling paper seems to use different testing methods to show properties of their sequences, which can make it hard to compare against other sample sequences.

My goal is to get as many implemented and tested as possible, including new ones as they come out, so this stuff is more accessible and usable by the folks who could benefit from it.

It's a lot of work for one person though, so Sample Zoo need your help!

# Other Software Used

* **STB** - https://github.com/nothings/stb.  This is used to read and write images, and render true type text. Very cool set of header only libraries from Sean Barrett https://twitter.com/nothings.
* **Premake5** - a nice way to generate project and solution files from code.  Because premake scripts are lua, I also have the premake script call into the lua files that generate code and documentation - such as the table of contents page!  https://premake.github.io/
* **simple_fft** - https://github.com/d1vanov/Simple-FFT.  A header only library implementing the fast discrete fourier transform.  Used for frequency analysis.
