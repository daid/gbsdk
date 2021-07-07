# Project configuration

Main project configuration is set in the Makefile in your project directory. It configures the following settings:

## PROJECT_NAME

Sets the name of the resulting rom file. As well as the title stored in this rom (which some emulators show, but otherwise has no effect)

## MBC

This defines which [MBC](https://gbdev.io/pandocs/MBCs.html) is used for the rom. As well as which extra features this MBC should support.

For example, if you want a large rom with save games, you'll most likely need `MBC := MBC5+RAM+BATTERY`

**TODO: There is no way to set SRAM size yet...**

## TARGETS

This defines which hardware the rom targets. It can be any combination of DMG, CGB and SGB.

For example: `TARGETS := DMG CGB` create a rom that targets both the DMG and CGB, and should be able to run on both, and enables color features on the CGB.

Note that not having a target enabled will not expose the relevant API functions. So if SGB is not in the TARGETS list, then for example the `sgb_send()` function will not be available.