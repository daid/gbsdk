#ifndef GBSDK_SYSTEM_H
#define GBSDK_SYSTEM_H

#include <stdint.h>
#include <stdbool.h>

#define CPU_DMG 0x01 // Dot Matrix Game
#define CPU_CGB 0x11 // Color GameBoy
#define CPU_MGB 0xFF // Mini GameBoy (Pocket GameBoy)

extern uint8_t cpu_type; // DMG, CGB or MGB
extern bool system_is_gba; // Is the system a GBA or a CGB? (Only valid if cpu_type == CPU_CGB)

#endif//GBSDK_SYSTEM_H