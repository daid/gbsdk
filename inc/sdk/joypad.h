#ifndef GBSDK_JOYPAD_H
#define GBSDK_JOYPAD_H

#include <stdint.h>

#define PADF_DOWN   0x80
#define PADF_UP     0x40
#define PADF_LEFT   0x20
#define PADF_RIGHT  0x10
#define PADF_START  0x08
#define PADF_SELECT 0x04
#define PADF_B      0x02
#define PADF_A      0x01

extern uint8_t joypad_state;
extern uint8_t joypad_pressed;

void joypad_update();

#endif//GBSDK_JOYPAD_H
