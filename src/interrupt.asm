include "sdk/hardware.inc"


SECTION "VBlankInterrupt", ROM0[$0040]
    reti
SECTION "STATInterrupt", ROM0[$0048]
    reti
SECTION "TimerInterrupt", ROM0[$0050]
    reti
SECTION "SerialInterrupt", ROM0[$0058]
    reti
SECTION "JoypadInterrupt", ROM0[$0060]
    reti
