#ifndef GBSDK_VRAM_H
#define GBSDK_VRAM_H

#include <stdint.h>
#include <sdk/hardware.h>

//Copy to VRAM with STAT checks.
void vram_memcpy(uint16_t dst, void* src, uint16_t size);
void vram_memset(uint16_t dst, uint8_t value, uint16_t size);

inline void vram_set(uint16_t dst, uint8_t value) {
    while(rSTAT & STAT_BUSY) {}
    *((uint8_t*)dst) = value;
}

#endif//GBSDK_VRAM_H
