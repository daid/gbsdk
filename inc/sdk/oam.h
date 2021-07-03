#ifndef GBSDK_OAM_H
#define GBSDK_OAM_H

#include <stdint.h>
#include "hardware.h"

#define OAM_PRI     0b10000000
#define OAM_YFLIP   0b01000000
#define OAM_XFLIP   0b00100000
#define OAM_PAL0    0b00000000
#define OAM_PAL1    0b00010000
#if CGB
#define OAM_BANK0   0b00000000
#define OAM_BANK1   0b00001000
#define OAM_PALMASK 0b00000111
#endif

struct oam_entry {
    uint8_t y;
    uint8_t x;
    uint8_t tile;
    uint8_t attr;
};
extern struct oam_entry shadow_oam[40];

void oam_init() __preserves_regs(b);
void oam_dma_copy() __preserves_regs(b, c, d, e, h, l);

#endif//GBSDK_OAM_H
