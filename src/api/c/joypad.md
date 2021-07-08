# Joypad

The joypad functionality is provided by `sdk/joypad.h`.

It provides the following features:

- `void joypad_update(void)`: function to update the joypad values. This should usually be called once a frame.
- `uint8_t joypad_state`: variable that contains buttons held at the last `joypad_update()` call.
- `uint8_t joypad_pressed`: variable that contains buttons that where pressed down at the last `joypad_update()` call but not at the `joypad_update()` call before that (newly pressed buttons)
- `PAD_DOWN PAD_UP PAD_LEFT PAD_RIGHT PAD_START PAD_SELECT PAD_B PAD_A`: bit definitions for `joypad_state` and `joypad_pressed`



Example usage:
```c
#include <sdk/joypad.h>
#include <sdk/hardware.h>

uint8_t value;

void function() {
	while(1) {
		// Update the joypad_state and joypad_pressed variables
		update_joypad();

		// Break out of the loop if start or select is pressed
		if (joypad_pressed & (PAD_START | PAD_SELECT))
			break;

		// If left is hold down, change some value
		if (joypad_state & PAD_LEFT)
			value = value - 1;

		//Assumes vblank interrupt is setup
		HALT();
	}
}