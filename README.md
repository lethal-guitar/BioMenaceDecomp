# BioMenace decompilation (WIP)

This is a work in progress decompilation/source code reconstruction of the game BioMenace,
released by Apogee Software in 1993 for MS-DOS.

Based on [K1n9_Duk3's reconstruction of Commander Keen 4 source code](https://github.com/sparky4/keen4-6).
BioMenace is based on the same engine and thus shares a lot of code with the 2nd Keen trilogy.
It's far from identical though - almost all of the game logic is completely unique to this game,
and many other parts of the code have also been modified.

In the meantime, K1n9_Duk3 has also released a complete code reconstruction of the whole game:
* [Announcement post](https://pckf.com/viewtopic.php?t=18039)
* [Download](https://k1n9duk3.shikadi.net/files/modding/bmsource.zip)


## Current state

This code produces a 100% identical binary to `BMENACE1.EXE` from the freeware release of the game (SHA-256 `b91ed9c1e8a7a47cff209401f50aa7bc2eca9b42738d7f6aa5e6b55ed35fae7a`). The shareware version v1.1 (SHA-256 `c47d1114263b8cf3f27b776c8a858b4f89dc59d1a2cccfdddffc194277adc008`) can also be perfectly reproduced. Episodes 2 and 3 are not currently covered. Since K1n9_Duk3's recreation (see above) fully covers these, I most likely won't do any more work on this project.


## Compiling the code

A copy of Borland C++ 2.0 is required, and a DOS environment to run it in (real or emulated).
The compiler is expected to be installed at `C:\BCC_20` by default.
The `BIN` subdirectory of the installation should be in the `PATH`.

Within the DOS environment, `cd` into the directory containing the code and run `make`.
This creates a file called `BMENACE1.EXE`, but it still needs to be compressed before it matches the original version.
Run `LZEXE\LZEXE.EXE BMENACE1.EXE` to do so, and a perfectly matching file should be produced.

To build the shareware version, uncomment the corresponding `#define` near the top of `ID_HEADS.H`, and comment out the `FREEWARE` `#define`.

In order to play the game using an `EXE` built from this code, the game data from the original release is required -
this repository doesn't contain any data files.
