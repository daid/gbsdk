include "sdk/hardware.inc"

SECTION "gbsdk_systeminfo_ram", WRAM0
_cpu_type::
wCpuType:: ds 1

IF CGB
_system_is_gba::
wSystemIsGba:: ds 1
ENDC


SECTION "Header", ROM0[$100]
    di
    jp startRom
    ds $150 - @

SECTION "Init", ROMX, BANK[1]
startRom:
    ld   sp, $E000 ; Set stack pointer to the top of WRAM
    ld [wCpuType], a ; Detect system type based on initial register state
IF CGB
    ld a, b
    ld [wSystemIsGba], a
ENDC
    call ___globalsInitCode ; init C globals
    call _main
    db   $DD ; lock up if main returns ($DD is an invalid opcode)


SECTION FRAGMENT "GSINIT", ROMX, BANK[1]
___globalsInitCode:
    ; This will be the first fragment of GSINIT.
    ld   bc, sizeof("INITIALIZER")
    assert sizeof("INITIALIZER") == sizeof("INITIALIZED")
    ld   hl, startof("INITIALIZER")
    ld   de, startof("INITIALIZED")
:   ld   a, b
    or   c
    jr   z, :+
    ld   a, [hl+]
    ld   [de], a
    inc  de
    dec  bc
    jr   :-
:

SECTION FRAGMENT "INITIALIZER", ROMX, BANK[1]
    ; This will be the first fragment of INITIALIZER.
    ; Other fragments can fill this with data which will be copied to WRAM in the "INITIALIZED" fragment

SECTION FRAGMENT "INITIALIZED", WRAM0
    ; This will be the first fragment of INITIALIZED.
