#ifndef GBSDK_OAM_H
#define GBSDK_OAM_H

#include <stdint.h>
#include <sdk/hardware.h>

#define OAM_Y_OFS 16 // add this to a screen-relative Y position to get an OAM Y position
#define OAM_X_OFS 8 // add this to a screen-relative X position to get an OAM X position

struct oam_entry {
    uint8_t y;
    uint8_t x;
    uint8_t tile;
    uint8_t attr;
};
extern struct oam_entry shadow_oam[40];

void oam_init(void) __preserves_regs(b);
void oam_dma_copy(void) __preserves_regs(b, c, d, e, h, l);

#endif//GBSDK_OAM_H
