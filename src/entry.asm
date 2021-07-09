include "sdk/hardware.inc"


SECTION "Header", ROM0[$100]
    di
    jp startRom
    ds $150 - @

SECTION "Init", ROMX, BANK[1]
startRom:
    ld   sp, $E000
    call globalsInit ; init C globals
    call _main
    db   $DD ; lock up if main returns ($DD is an invalid opcode)


SECTION FRAGMENT "GSINIT", ROMX, BANK[1]
globalsInit:
    ; This will be the first fragment of GSINIT.
