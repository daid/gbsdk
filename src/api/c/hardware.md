# Registers

By including the file `sdk/hardware.h` you will get access to all the registers mentioned in the [Pan Docs](https://gbdev.io/pandocs/). See the [include file](https://github.com/daid/gbsdk/blob/master/inc/sdk/hardware.h) for all possible registers and bit definitions.

Each register is prefixed with an `r`, so `LCDC` becomes `rLCDC`. Registers that are CGB only will only be available of the CGB is enabled in the project configuration.

Next to the registers, a few other macros are provided for working with interrupts:
- `HALT()`: execute the `halt` instruction, which will wait for an interrupt.
- `DISABLE_INTERRUPTS()`: Disables the global interrupt mask, no interrupts will execute interrupt handlers.
- `ENABLE_INTERRUPTS()`: Enable the global interrupt mask. Any enabled interrupt in `rIE` will execute the interrupt handler.

Examples:
```c
#include <gbsdk/hardware.h>


void function() {
	//Enable the LCD with the background and the window enabled.
	// Use the memory at 0x9800 for the background tilemap, and at 0x9C00 for the window tilemap.
	rLCDC = LCDC_ON | LCDC_WINON | LCDC_WIN9C00 | LCDC_BGON;
	
	//Set a default background palette with all 4 colors.
	rBGP = 0b11100100;
	
	//Set the window start somewhere on the screen.
	rWX = 100;
	rWY = 100;
}
```