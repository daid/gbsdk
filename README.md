# Gameboy Software Development Kit

This is the Gameboy software development kit. For mixed assembly and C programming. Note that this isn't a mature project yet.

If you want to do C programming for the Gameboy, https://github.com/gbdk-2020/gbdk-2020 is much more mature.

If you want to do assembly programming for the Gameboy, https://rgbds.gbdev.io/ is the goto toolchain.

# But... but...? Why this then?

This project has a few goals:

* Thin/no abstractions. GBDK-2020 is an oddball of low level functions, badly named functions and high level functions with horrible performance and side effects.
* Mixing of C code with ASM code, without subjecting yourself to the asxxxx syntax.
* A different linker. By using the rgbds linker instead of the SDCC linker, a bunch of features that exernal tools provide on gbdk-2020 are standard.

# Usage

To use this, you need to have installed:

* sdcc (version 4.2.0)
* rgbds (version 0.5.1)
* python (version 3.6 or newer)
* A strong will, and a bit of crazy.

See https://github.com/daid/gbsdk-template for a ready to use template of a project setup.
