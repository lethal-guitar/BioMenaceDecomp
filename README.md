# BioMenace decompilation (WIP)

This is a (heavily work in progress) decompilation/source code reconstruction of the game BioMenace,
released by Apogee Software in 1993 for MS-DOS.

Based on [K1n9_Duk3's reconstruction of Commander Keen 4 source code](https://github.com/sparky4/keen4-6).
BioMenace uses the same engine and thus shares a lot of code with the 2nd Keen trilogy.


## Current state

Only the episode 1 Shareware EXE v1.1 is currently covered - the original version, not the freeware release (which contains registered version episode 1).

All of the engine, menu system, and game loop/infrastructure code has been recreated and is mostly a byte-for-byte perfect match with the original EXE (aside from some function and variable addresses which aren't matching yet). About half of the player control code has also been recreated. However, all the actor logic (enemies, items, interactive objects etc.) is still missing.

Overall, about 75 % of all code and 92 % of all data has been recreated.
Out of that, only 27 % of the game-specific code has been done so far.

Some variables and functions don't have meaningful names yet, and many places use magic numbers instead of enum values/constants.


### Progress overview

| What | Bytes | % done |
| --- | --- | --- |
| All code | 99,783 / 131,744 | 75.7 % |
| Game logic code | 12,166 / 44,127 | 27.6 % |
| Data | 82,880 / 89,984 | 92.1 % |


### TODO

* Complete `GRAPHBM1.H`
* Complete `AUDIOBM1.H`
* Fully decompile `B1_PLAY2.C`
* Fully decompile `ScanInfoPlane` function in `BM_SPEC.C`
* Decompile `B1_ACT{1,2,3}.C`
* Make BSS variable order match perfectly in `BM_GAME3.C` and `BM_PLAY1.C`
* Assign meaningful names to all functions and variables
* Do registered version episode 1
* Do episode 2
* Do episode 3


## Compiling the code

A copy of Borland C++ 2.0 is required, and a DOS environment to run it in (real or emulated).
The compiler is expected to be installed at `C:\BCC_20` by default.
The `BIN` subdirectory of the installation should be in the `PATH`.

Within the DOS environment, `cd` into the directory containing the code and run `make -a`.
This creates a file called `BMENACE1.EXE`.

Running this file isn't too useful at this point. It will launch and you can navigate all the menus and start or load a game. You'll be able to walk and jump around in the levels. But nothing else is working.
