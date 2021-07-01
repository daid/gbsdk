include "hardware.inc"

SECTION "gbsdk_vram_functions", ROM0
_vram_memcpy::
    ld   hl, sp + 7
    ld   a, [hl-]
    ld   d, a
    ld   a, [hl-]
    ld   e, a
    or   a, d
    jr   Z, .skip

    ; size -> de
    push bc
     ld   a, [hl-]
     ld   b, a
     ld   a, [hl-]
     ld   c, a
     ld   a, [hl-]
     ld   l, [hl]
     ld   h, a
     inc  d
     inc  e
     ; src -> bc, dst -> hl, size -> de
     jr   .start

.copy_loop:
     ldh  a, [rSTAT]
     and  a, STATF_BUSY
     jr   nz, .copy_loop
     ld   a, [bc]
     ld   [hl+], a
     inc  bc
.start:
     dec e
     jr nz, .copy_loop
     dec d
     jr nz, .copy_loop

    pop bc
.skip:
    ld   hl, sp + 2
    ld   e, [hl]
    inc  hl
    ld   d, [hl]
    ret
