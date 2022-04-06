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
    ; src is in bc, dst is in de, size is on the stack

    ld   hl, sp + 2
    ld   a, [hl+]
    ld   h, [hl]
    ld   l, a
    or   a, h
    ret  z
    ; size -> hl

    ld   a, h
    ld   h, d
    ld   d, a

    ld   a, l
    ld   l, e
    ld   e, a
    ; swap hl and de, so now:
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

    ret

_vram_memset::
    ; value is in a, dst is in de, size is on the stack
    ld   c, a
    ; value -> c

    ld   hl, sp + 2
    ld   a, [hl+]
    ld   h, [hl]
    ld   l, a
    or   a, h
    ret  z
    ; size -> hl

    ld   a, h
    ld   h, d
    ld   d, a

    ld   a, l
    ld   l, e
    ld   e, a
    ; swap hl and de, so now:
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

    ret

IF CGB

_cgb_background_palette::
    ld   h, d
    ld   l, e
    ld   a, BCPSF_AUTOINC
    ldh  [rBCPS], a
    ld   e, 8*4*2
:   ld   a, [hl+]
    ldh  [rBCPD], a
    dec  e
    jr   nz, :-
    ret

_cgb_object_palette::
    ld   h, d
    ld   l, e
    ld   a, OCPSF_AUTOINC
    ldh  [rOCPS], a
    ld   e, 8*4*2
:   ld   a, [hl+]
    ldh  [rOCPD], a
    dec  e
    jr   nz, :-
    ret

ENDC
