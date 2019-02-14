# SampleZoo
Simple copy/paste-able implementations of sampling patterns, with objective and subjective tests to compare them.

Created by Alan Wolfe (alan.wolfe@gmail.com)

Building and running this code: [building](building.md)

Everything in this repository is under the [MIT License](LICENSE) unless otherwise stated in the source file.

Full list of contributors here: [credits](credits.md)

Information on how to contribute to this project: [contributing](contributing.md)

## Samples & Test Documentation

[TOC](toc.md) - Table of Contents

## Why Does This Exist??

My interest in sampling patterns is mainly for use in numerical integration techniques in real time graphics.  In that situation, you usually want a sequence that will converge with as few samples as possible, and give a pleasing error pattern when it hasn't fully converged.

This stuff is surprisingly nuanced, and new sampling techniques come out every year as researchers continue to push the envelope.

To get a taste of things, check out the page on regularly spaced samples:

[Regular Sampling](src/samples/_1d/regular/regular.md)

## Other Software Used

* **STB** - stb_image and stb_image write from https://github.com/nothings/stb.  This is used to read and write images. Very cool set of header only libraries from Sean Barrett https://twitter.com/nothings.
* **Premake5** - a nice way to generate project and solution files from code.  https://premake.github.io/
