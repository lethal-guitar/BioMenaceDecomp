# BioMenace decompilation (WIP)

This is a work in progress decompilation/source code reconstruction of the game BioMenace,
released by Apogee Software in 1993 for MS-DOS.

Based on [K1n9_Duk3's reconstruction of Commander Keen 4 source code](https://github.com/sparky4/keen4-6).
BioMenace is based on the same engine and thus shares a lot of code with the 2nd Keen trilogy.
It's far from identical though - almost all of the game logic is completely unique to this game,
and many other parts of the code have also been modified.


## Current state

This code produces a 100% identical binary to `BMENACE1.EXE` from the Shareware version v1.1 of the game (SHA-256 `c47d1114263b8cf3f27b776c8a858b4f89dc59d1a2cccfdddffc194277adc008`). Episodes 2 and 3 are still work in progress, as is the registered version episode 1.


### TODO

* Do registered version episode 1
* Do episode 2
* Do episode 3


## Compiling the code

A copy of Borland C++ 2.0 is required, and a DOS environment to run it in (real or emulated).
The compiler is expected to be installed at `C:\BCC_20` by default.
The `BIN` subdirectory of the installation should be in the `PATH`.

Within the DOS environment, `cd` into the directory containing the code and run `make -a`.
This creates a file called `BMENACE1.EXE`.
Running `LZEXE\LZEXE.EXE BMENACE1.EXE` then produces an identical file to the original Shareware release.

In order to play the game using this file, the game data from the original release is required since
this repository doesn't contain any data files.
