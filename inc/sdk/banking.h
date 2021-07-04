#ifndef GBSDK_BANKING_H
#define GBSDK_BANKING_H

#include <stdint.h>

extern __sfr currentBank;
#define SET_BANK(bank_nr) { \
        currentBank = bank_nr; \
        *((uint8_t*)0x2000) = bank_nr; \
    }

#endif//LIB_BANKING_H
