include "sdk/hardware.inc"

IF SGB

SECTION "gbsdk_sgb_functions", ROM0
_sgb_send::
    pop  de
    pop  hl
    ; hl=pointer to data to send

    ; SGB RESET pulse
    xor  a
    ldh  [rP1], a
    push hl ; done here for delay reasons
    cpl
    ldh  [rP1], a
    push de ; done here for delay reasons
    ld   e, 16 ; amount of bytes to send

.byteLoop:
    ld   a, [hl+]
    ld   d, a   ; byte to send in d
    ld   c, 8 ; amount of bits to send

.bitLoop:
    bit  0, d
    ld   a, P1F_5
    jr   z, .zero
    ld   a, P1F_4
.zero:
    ldh  [rP1], a
    rr   d                ; 2cycles
    ld   a, P1F_5 | P1F_4 ; 2cycles
    dec  c                ; 1cycle
    ldh  [rP1], a
    jr   nz, .bitLoop
    dec  e
    jr   nz, .byteLoop
    ld   a, P1F_5
    ldh  [rP1], a
    ldh  [rP1], a ; (3)
    ldh  [rP1], a ; (3)
    xor  a        ; (1)
    ldh  [rP1], a

    ret

ENDC
