# Building

This project uses premake5 and includes a windows binary for that downloaded from https://premake.github.io/.

To create the solution in windows, open a command prompt in the main folder and run: ./premake5.exe vs2017

The project and solution files will be inside the build folder, as well as any intermediary files from compiling, and the final executables.

Note that this creates a solution for visual studio 2017, but other targets are supported.  See this page for more information: https://github.com/premake/premake-core/wiki/Using-Premake

Once the solution is created, open it up and compile / run as normal.
