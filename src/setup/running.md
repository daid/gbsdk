# Building & Running

## Building your project

Building your project is the easest thing ever. Just run the command: `make -j4`

You'll first have to `cd` to the directory of your project. So, for example, on windows, if you have your project in your `Documents`. You'll need to open the gbsdk-bash.exe and run the following steps:
```sh
cd ~/Documents/MostAwesomeGameboyProjectEver
make -j4
```

With a bit of luck, you'll get a `MostAwesomeGameboyProjectEver.gb` file.

## Running your rom

There are many ways to run your rom. All emulators listed here have very high emulation accuracy, meaning that if they run in the emulator, it's pretty much ensured that it will run on real hardware.

* [BGB](https://bgb.bircd.org/) is pretty much the goto emulator on Windows. It has debugging tools, but only for assembly.
* [Emulicious](https://emulicious.net/) is another excellent choice. It has debugging tools. (TODO: Check if C level debugging works with the vscode extension)
* [SameBoy](https://sameboy.github.io/) excellent emulator. But, debugging tools are only available on MacOS.
* [EverDrive-GB X7](https://krikzz.com/store/home/46-everdrive-gb.html) while emulators are great. Nothing can replace testing on real hardware. The EverDrive flash carts are the top of the line carts.
	The X7 has all the features you would want, but is also the most expensive model. The X3 or X5 could be enough for your usage.
* [EZ-Flash Jr](https://www.ezflash.cn/product/ezflash-junior/) the budget flash cart. It has most of the same features as the EverDrive-GB X7, but is cheaper. However, it's power consumption is higher so batteries run dry quicker.

One important reason to run on real hardware is the screen. The screens of the gameboy are quite different (in a bad way) from modern LCDs, colors will look different, motion blur on the DMG is a real thing. While emulators have options to emulate this,
it never really matches the real deal.

## Note

In some cases, if you rename files, you might get an `No rule to make target` error. In this case first run `make clean`. This is an issue that still needs to be solved in GBSDK.

**Stay away from VisualBoyAdvance** this emulator is used a lot, but it is buggy and broken accuracy wise. There is a good chance that you make your rom bug free on this emulator and that it does not run
on real hardware.