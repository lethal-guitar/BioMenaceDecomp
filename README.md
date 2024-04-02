# BioMenace decompilation (WIP)

This is a (heavily work in progress) decompilation/source code reconstruction of the game BioMenace,
released by Apogee Software in 1993 for MS-DOS.

Based on [K1n9_Duk3's reconstruction of Commander Keen 4 source code](https://github.com/sparky4/keen4-6).
BioMenace uses the same engine and thus shares a lot of code with the 2nd Keen trilogy. Almost all of the game logic is completely unique to this game though.


## Current state

Only the episode 1 Shareware EXE (v1.1) is currently covered - the original version, not the freeware release (which contains registered version episode 1).

All of the engine, menu system, and game loop/infrastructure code has been recreated and is mostly a byte-for-byte perfect match with the original EXE (aside from some function and variable addresses which aren't matching yet). The player control code has also been recreated. However, practically all of the actor logic (enemies, items, interactive objects etc.) is still missing.

Overall, about 90 % of the code has been recreated.

Some variables and functions don't have meaningful names yet, and many places use magic numbers instead of enum values/constants.


### Progress overview

| What | Bytes | % done |
| --- | --- | --- |
| All code | 119,685 / 131,744 | 90.85 % |
| Game logic code | 32,086 / 44,127 | 72.67 % |
| Data | 89,984 / 89,984 | 100 % |


### TODO

* Complete `AUDIOBM1.H`
* Decompile `BM_ACT{2,3}.C`
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
