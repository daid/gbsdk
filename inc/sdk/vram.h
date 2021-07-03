#ifndef GBSDK_VRAM_H
#define GBSDK_VRAM_H

#include <stdint.h>
#include <sdk/hardware.h>

//Turn off the LCD, with the proper checks that this happens during VBLANK
void lcd_off() __preserves_regs(b, c, d, e, h, l);

//Copy to VRAM with STAT checks, so these function are safe to write to VRAM at any time.
void vram_memcpy(uint16_t dst, void* src, uint16_t size) __preserves_regs(b, c);
void vram_memset(uint16_t dst, uint8_t value, uint16_t size) __preserves_regs(b, c);
inline void vram_set(uint16_t dst, uint8_t value) {
    while(rSTAT & STAT_BUSY) {}
    *((uint8_t*)dst) = value;
}

#endif//GBSDK_VRAM_H
