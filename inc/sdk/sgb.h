#ifndef GBSDK_SGB_H
#define GBSDK_SGB_H

#include <stdint.h>

#if SGB

#define SGB_PAL01       0x00    //Set SGB Palette 0 & 1
#define SGB_PAL23       0x01    //Set SGB Palette 2 & 3
#define SGB_PAL03       0x02    //Set SGB Palette 0 & 3
#define SGB_PAL12       0x03    //Set SGB Palette 1 & 2
#define SGB_ATTR_BLK    0x04    //"Block" Area Designation Mode
#define SGB_ATTR_LIN    0x05    //"Line" Area Designation Mode
#define SGB_ATTR_DIV    0x06    //"Divide" Area Designation Mode
#define SGB_ATTR_CHR    0x07    //"1CHR" Area Designation Mode
#define SGB_SOUND       0x08    //Sound On/Off
#define SGB_SOU_TRN     0x09    //Transfer Sound PRG/DATA
#define SGB_PAL_SET     0x0A    //Set SGB Palette Indirect
#define SGB_PAL_TRN     0x0B    //Set System Color Palette Data
#define SGB_ATRC_EN     0x0C    //Enable/disable Attraction Mode
#define SGB_TEST_EN     0x0D    //Speed Function
#define SGB_ICON_EN     0x0E    //SGB Function
#define SGB_DATA_SND    0x0F    //SUPER NES WRAM Transfer 1
#define SGB_DATA_TRN    0x10    //SUPER NES WRAM Transfer 2
#define SGB_MLT_REQ     0x11    //Controller 2 Request
#define SGB_JUMP        0x12    //Set SNES Program Counter
#define SGB_CHR_TRN     0x13    //Transfer Character Font Data
#define SGB_PCT_TRN     0x14    //Set Screen Data Color Data
#define SGB_ATTR_TRN    0x15    //Set Attribute from ATF
#define SGB_ATTR_SET    0x16    //Set Data to ATF
#define SGB_MASK_EN     0x17    //Game Boy Window Mask
#define SGB_OBJ_TRN     0x18    //Super NES OBJ Mode

#define SGB_HEADER(command, length) ((uint8_t)(((command) << 3) | (length)))

void sgb_send(const uint8_t* packet) __preserves_regs(b);
#endif

#endif
