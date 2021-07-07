# Summary

The goal of GBSDK is as following:

**Provide an environment to allow C and Assembly programming for the Gameboy, with a low amount of abstraction.**

Also note that this targets the following hardware:
* DMG: Origonal gameboy (First version, known as the gray brick)
* SGB: Super Gameboy (Running gameboy games on the Super Nintendo)
* CGB: Gameboy Color (Adds color support and a few more minor features)

*Note that the Gameboy Advanced is a very different device. And not part of the targets for GBSDK. The Gameboy Advanced has a Gameboy Compatibility mode, which is essentially a Gameboy Color (CGB).
But full Gameboy Advanced development information can be found on [gbadev](https://gbadev.net/)]*

To compare it with two other well known environments:

## [GBDK-2020](https://github.com/gbdk-2020/gbdk-2020)

GBDK-2020 provides a C programming environment. It hides a few hardware details behind abstractions, and it provides high level functions for some parts, while low level for other parts.
Which results in people not understanding what the hardware is doing and why things are not working as expected.

A simple example is `printf()` which GBDK-2020 provides. It allows writting text to the screen. But, the Gameboy does not have any text output, it has a tile based rendering.
So this uses a large amount of available graphic tiles to provide this text drawing facility. It makes drawing text easy, but also adds multiple layers of hidden behavior.

Both GBDK-2020 and GBSK use [sdcc](http://sdcc.sourceforge.net/) as a C compiler. So the basic C support is the same, but the libraries and build systems are very different.

## [rgbds](https://rgbds.gbdev.io/)

rgbds is the nr1 used assembler for Gameboy programming. If you want to do assembly for the gameboy, then rgbds is your friend. And GBSDK uses rgbds as well!

However, stand alone it only provides the assembler and nothing more. No default project setup, no intergration with C, everything else you'll need to do yourself.

## So, GBSDK

So, GBSDK stands a bit in the middle between rgbds and GBDK-2020. It does provide the facilities to program in C. But it does not provide high level abstractions, it only provides
the facilities to access the hardware. It also integrates with rgbds as an assembler, instead of using the asxxxx assembler that sdcc uses by default.