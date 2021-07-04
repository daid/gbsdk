INCLUDE "sdk/hardware.inc"

SECTION "BankingHRAM", HRAM
_currentBank:: ds 1

SECTION "BankingCode", ROM0
bankedCall::
___sdcc_bcall_ehl::
    ldh  a, [_currentBank]
    push af
    ld   a, e
    ldh  [_currentBank], a
    ld   [rROMB0], a
    rst  callHL
    pop  af
setCurrentBank::
    ldh  [_currentBank], a
    ld   [rROMB0], a
    ret

SECTION "callHL", ROM0[$0008]
callHL::
___sdcc_call_hl::
    jp   hl
