#ifndef GBSDK_VRAM_H
#define GBSDK_VRAM_H

#include <stdint.h>

//Copy to VRAM with STAT checks.
void vram_memcpy(void* dst, void* src, uint16_t size);

#endif//GBSDK_VRAM_H
