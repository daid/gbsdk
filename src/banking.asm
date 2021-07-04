INCLUDE "sdk/hardware.inc"

SECTION "BankingHRAM", HRAM
wCurrentBank::
_current_bank:: ds 1

SECTION "BankingCode", ROM0
bankedCall::
___sdcc_bcall_ehl::
    ldh  a, [wCurrentBank]
    push af
    ld   a, e
    ldh  [wCurrentBank], a
    ld   [rROMB0], a
    rst  callHL
    pop  af
setCurrentBank::
    ldh  [wCurrentBank], a
    ld   [rROMB0], a
    ret

SECTION "callHL", ROM0[$0008]
callHL::
___sdcc_call_hl::
    jp   hl
