#ifndef GBSDK_BANKING_H
#define GBSDK_BANKING_H

#include <stdint.h>

extern __sfr current_bank;

inline void switch_bank(bank_nr) {
    current_bank = bank_nr;
    *((uint8_t*)0x2000) = bank_nr;
}

#endif//LIB_BANKING_H
