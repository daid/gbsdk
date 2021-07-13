# Banking

Banking is needed to fit more then 32KiB of ROM into a single Cartridge.
The general process is as follows:
> * Data and code is contained in banks.
> * Data and code in bank0 is always available.
> * Only one other bank is active at the same time, meaning that code in one bank cannot access code/data in another.
> * It is possible to call code in another bank from a different bank, if setup correctly.

Banking is one of the those things that makes Gameboy Progamming more complex.
You need to think about what code you put in bank0. And what can be placed in banks.


Banking with gbsdk (and sdcc) works per `.c` file. Each file can be assigned a bank. And all code/data of that will will then be placed inside that specific bank.

You can use:
```c
#pragma bank 1 // Places this .c file in bank 1
#pragma bank auto // Places this .c file in a bank assigned by the compiler.
```

> **Note:** Multiple `.c` files can be placed in the same bank, and the `auto` option can place multiple things in the same bank.

## Calling functions in other banks

TODO
