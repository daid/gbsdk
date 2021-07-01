include "sdk/hardware.inc"

SECTION "gbsdk_joypad_ram", WRAM0
_joypad_state::
wJoypadState:: ds 1
_joypad_pressed::
wJoypadPressed:: ds 1


SECTION "gbsdk_joypad_functions", ROM0
_joypad_update::
    ; Call this routine once per frame to update the joypad related variables.
    ; Routine also returns the currently pressed buttons in the a register.
    ld   hl, rP1
    ld   [hl], P1F_GET_BTN
    ; After the initial enable we need to read twice to ensure
    ; we get the proper hardware state on real hardware
    ld   a, [hl]
    ld   a, [hl]
    ld   [hl], P1F_GET_DPAD
    cpl  ; Inputs are active low, so a bit being 0 is a button pressed. So we invert this.
    and  PADF_A | PADF_B | PADF_SELECT | PADF_START
    ld   e, a  ; Store the lower 4 button bits in e

    ; We need to read rP1 8 times to ensure the proper button state is available.
    ; This is only needed on real hardware, as it takes a while for the
    ; inputs to change state back from the first set.
    ld   d, 8
:   ld   a, [hl]
    dec  d
    jr   nz, :-
    ld   [hl], P1F_GET_NONE ; Disable the joypad inputs again, saves a tiny bit of power and allows the lines to settle before the next read

    swap a ; We want the directional keys as upper 4 bits, so swap the nibbles.
    cpl  ; Inputs are active low, so a bit being 0 is a button pressed. So we invert this.
    and  PADF_RIGHT | PADF_LEFT | PADF_UP | PADF_DOWN
    or   e
    ld   e, a

    ; Compare the new joypad state with the previous one, and store the
    ; new bits in wJoypadPressed
    ld   hl, wJoypadState
    xor  [hl]
    and  e
    ld   [wJoypadPressed], a
    ld   a, e
    ld   [wJoypadState], a
    ret
