#ifndef GBSDK_JOYPAD_H
#define GBSDK_JOYPAD_H

#include <stdint.h>

#define PAD_DOWN   0x80
#define PAD_UP     0x40
#define PAD_LEFT   0x20
#define PAD_RIGHT  0x10
#define PAD_START  0x08
#define PAD_SELECT 0x04
#define PAD_B      0x02
#define PAD_A      0x01

extern uint8_t joypad_state;
extern uint8_t joypad_pressed;

void joypad_update(void) __preserves_regs(b, c);

#endif//GBSDK_JOYPAD_H
