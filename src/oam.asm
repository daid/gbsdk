include "sdk/hardware.inc"

SECTION "gbsdk_oam_memory", WRAM0, ALIGN[8]
_shadow_oam:: ; OAM Memory is for 40 sprites with 4 bytes per sprite
wShadowOAM::
  ds 40 * 4
.end:

SECTION "gbsdk_oam_init_function", ROMX, BANK[1]
oamInit::
_oam_init::
    ld   hl, wShadowOAM
    xor  a
    ld   c, wShadowOAM.end - wShadowOAM
:   ld   [hl+], a
    dec  c
    jr   nz, :-

    ld   hl, hOAMCopyRoutine
    ld   de, oamCopyRoutine
    ld   c, hOAMCopyRoutine.end - hOAMCopyRoutine
:   ld   a, [de]
    inc  de
    ld   [hl+], a
    dec  c
    jr   nz, :-

    ; We directly copy to clear the initial OAM memory, which else contains garbage.
    jp   hOAMCopyRoutine


oamCopyRoutine:
LOAD "hram", HRAM
_oam_dma_copy::
hOAMCopyRoutine::
  ld   a, HIGH(wShadowOAM)
  ldh  [rDMA], a
  ld   a, $28
.wait:
  dec  a
  jr   nz, .wait
  ret
.end:
ENDL
