# LCD Control

Most of the LCD control features are handled by the [registers](hardware.md) directly, without any API abstraction.

* `rLCDC`: LCD on/off and various feature bits.
* `rSTAT` `rLY` `rLYC`: LCD runtime status and interrupt related.
* `rSCX` `rSCY`: Background render offset.
* `rWX` `rWY`: Window position.

The [pandocs](https://gbdev.io/pandocs/) section on [rendering](https://gbdev.io/pandocs/Rendering.html) explains all these registers really well.

There is one support function:
```c
void lcd_off(void);
```
This turns off the LCD in a proper way. Disabling the LCD at the wrong time can damage DMG hardware and thus should be avoided. This function will ensure that it is done properly.

> **Note:** It's usually bad form to turn of the LCD. Think very carefully what you are doing before you turn off the LCD. While it does enable faster copies to VRAM, the screen will turn white. This is noticable in Pokemon for example, where they fade to black, turn the screen off for a short while and then turn it back on. Causing a white flash.
