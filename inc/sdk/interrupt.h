#ifndef GBSDK_INTERRUPT_H
#define GBSDK_INTERRUPT_H

#include <stdint.h>


// Macro to define an interrupt routine.
#define ISR(vector) \
    void __isr_entry__ ## vector () __naked { \
        __asm__(" .pusharea"); \
        __asm__(" .area VECTOR_" #vector); \
        __asm__("   jp ___isr_vector__" #vector); \
        __asm__(" .poparea"); \
    } \
    void __isr_vector__ ## vector () __interrupt(vector) __critical
#define ISR_VBLANK() ISR(0x40)
#define ISR_STAT()   ISR(0x48)
#define ISR_TIMER()  ISR(0x50)
#define ISR_SERIAL() ISR(0x58)
#define ISR_JOYPAD() ISR(0x60)

// Defines for specific instructions related to interrupts
#define HALT() __asm__("halt")
#define DISABLE_INTERRUPTS() __asm__("di")
#define ENABLE_INTERRUPTS() __asm__("ei")

#endif//GBSDK_INTERRUPT_H
