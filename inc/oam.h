#ifndef GBSDK_OAM_H
#define GBSDK_OAM_H

#include <stdint.h>
#include "hardware.h"

struct oam_entry {
    uint8_t y;
    uint8_t x;
    uint8_t tile;
    uint8_t attr;
};
extern struct oam_entry shadow_oam[40];

void oam_init();
void oam_dma_copy();

#endif//GBSDK_OAM_H
