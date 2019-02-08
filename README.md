# SampleZoo
Simple copy/paste-able implementations of sampling patterns, with objective and subjective tests to compare them.

Information on building this code: [building](building.md)

Created by Alan Wolfe (alan.wolfe@gmail.com)

Everything in this repository is under the [MIT License](LICENSE) unless otherwise stated in the source file.

Full list of contributors here: [credits](credits.md)

Information on how to contribute to this project: [contributing](contributing.md)

## Why Does This Exist??

My interest in sampling patterns is mainly for use in numerical integration techniques in real time graphics.  In that situation, you usually want a sequence that will converge with as few samples as possible, and give a pleasing error pattern when it hasn't fully converged.

This stuff is surprisingly nuanced, and new sampling techniques come out every year as researchers continue to push the envelope.

To get a taste of things, check out the page on regularly spaced samples:

[Regular Sampling](src/samples/1d/regular/regular.md)

## Samples Documentation

[1D](src/samples/1d/1d.md) - 1 dimensional samples

## Sample Tests Documentation

[1D](src/tests/1d/1d.md) - 1 dimensional sampling tests

## Other Software Used

* **STB** - stb_image and stb_image write from https://github.com/nothings/stb.  This is used to read and write images. Very cool set of header only libraries from Sean Barrett https://twitter.com/nothings.
* **Premake5** - a nice way to generate project and solution files from code.  https://premake.github.io/
