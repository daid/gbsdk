#ifndef GBSDK_VRAM_H
#define GBSDK_VRAM_H

#include <stdint.h>
#include <sdk/hardware.h>

#if CGB
//Bits for the background attributes in the 2nd VRAM bank.
#define BG_PRI     0b10000000
#define BG_YFLIP   0b01000000
#define BG_XFLIP   0b00100000
#define BG_BANK0   0b00000000
#define BG_BANK1   0b00001000
#define BG_PALMASK 0b00000111
#endif

//Turn off the LCD, with the proper checks that this happens during VBLANK
void lcd_off() __preserves_regs(b, c, d, e, h, l);

//Copy to VRAM with STAT checks, so these function are safe to write to VRAM at any time.
void vram_memcpy(uint16_t dst, void* src, uint16_t size) __preserves_regs(b, c);
void vram_memset(uint16_t dst, uint8_t value, uint16_t size) __preserves_regs(b, c);
inline void vram_set(uint16_t dst, uint8_t value) {
    while(rSTAT & STAT_BUSY) {}
    *((uint8_t*)dst) = value;
}

#if CGB
#define PAL24(rgb) (((rgb & 0xF80000) >> 19) | ((rgb & 0x00F800) >> 6) | ((rgb & 0x0000F8) << 7))

void cgb_background_palette(uint16_t* palette) __preserves_regs(b, c);
void cgb_object_palette(uint16_t* palette) __preserves_regs(b, c);
inline void cgb_gdma(uint16_t dst, const void* src, uint8_t count) {
    rHDMA1 = ((uint16_t)src) >> 8;
    rHDMA2 = ((uint16_t)src) & 0xFF;
    rHDMA3 = dst >> 8;
    rHDMA4 = dst & 0xFF;
    rHDMA5 = count - 1;
}
inline void cgb_hdma(uint16_t dst, const void* src, uint8_t count) {
    rHDMA1 = ((uint16_t)src) >> 8;
    rHDMA2 = ((uint16_t)src) & 0xFF;
    rHDMA3 = dst >> 8;
    rHDMA4 = dst & 0xFF;
    rHDMA5 = (count - 1) | 0x80;
}
#endif

#endif//GBSDK_VRAM_H
