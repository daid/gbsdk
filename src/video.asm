include "sdk/hardware.inc"

SECTION "gbsdk_video_functions", ROM0
_lcd_off::
:   ldh  a, [rLY]
    cp   144
    jr   c, :-
    xor  a
    ldh  [rLCDC], a
    ret

_vram_memcpy::
    ld   hl, sp + 7
    ld   a, [hl-]
    ld   d, a
    ld   a, [hl-]
    ld   e, a
    or   a, d
    ret  z
    ; size -> de

    push bc
     ld   a, [hl-]
     ld   b, a
     ld   a, [hl-]
     ld   c, a
     ld   a, [hl-]
     ld   l, [hl]
     ld   h, a
     ; src -> bc, dst -> hl, size -> de
     inc  d
     inc  e
     jr   .start

.copy_loop:
     ldh  a, [rSTAT]
     and  a, STATF_BUSY
     jr   nz, .copy_loop
     ld   a, [bc]
     ld   [hl+], a
     inc  bc
.start:
     dec  e
     jr   nz, .copy_loop
     dec  d
     jr   nz, .copy_loop

    pop bc
    ret

_vram_memset::
    ld   hl, sp + 6
    ld   a, [hl-]
    ld   d, a
    ld   a, [hl-]
    ld   e, a
    or   a, d
    ret  z
    ; size -> de
    push bc
     ld   a, [hl-]
     ld   c, a
     ld   a, [hl-]
     ld   l, [hl]
     ld   h, a
     ; value -> c, dst -> hl, size -> de
     inc  d
     inc  e
     jr   .start

.copy_loop:
     ldh  a, [rSTAT]
     and  a, STATF_BUSY
     jr   nz, .copy_loop
     ld   a, c
     ld   [hl+], a
.start:
     dec  e
     jr   nz, .copy_loop
     dec  d
     jr   nz, .copy_loop

    pop bc
    ret

IF CGB

_cgb_background_palette::
    pop  de
    pop  hl
    push hl
    push de
    ld   a, BCPSF_AUTOINC
    ldh  [rBCPS], a
    ld   e, 8*4*2
:   ld   a, [hl+]
    ldh  [rBCPD], a
    dec  e
    jr   nz, :-
    ret

_cgb_object_palette::
    pop  de
    pop  hl
    push hl
    push de
    ld   a, OCPSF_AUTOINC
    ldh  [rOCPS], a
    ld   e, 8*4*2
:   ld   a, [hl+]
    ldh  [rOCPD], a
    dec  e
    jr   nz, :-
    ret

ENDC
