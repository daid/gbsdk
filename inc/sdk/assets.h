#ifndef GBSDK_ASSETS_H
#define GBSDK_ASSETS_H

#include <stdint.h>

#define EXTERN_ASSET(var_name) \
    extern const uint8_t var_name[]; \
    extern const uint8_t var_name ## _end[]; \
    extern const void __bank__ ## var_name

#define ASSET(var_name, filename) \
    void __ ## var_name ## __() __naked { \
        __asm__("_" #var_name "::"); \
        __asm__(".incbin \"_build/assets/" filename "\""); \
        __asm__("_" #var_name "_end::"); \
    } EXTERN_ASSET(var_name)


#endif//GBSDK_ASSETS_H
