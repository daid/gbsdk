#ifndef GBSDK_HARDWARE_H
#define GBSDK_HARDWARE_H

// Register for reading joy pad info. (R/W)
static volatile __sfr __at(0x00) rP1;

#define P1F_5 0b00100000 // P15 out port, set to 0 to get buttons
#define P1F_4 0b00010000 // P14 out port, set to 0 to get dpad
#define P1F_3 0b00001000 // P13 in port
#define P1F_2 0b00000100 // P12 in port
#define P1F_1 0b00000010 // P11 in port
#define P1F_0 0b00000001 // P10 in port

#define P1F_GET_DPAD P1F_5
#define P1F_GET_BTN  P1F_4
#define P1F_GET_NONE (P1F_4 | P1F_5)


// Serial Transfer Data (R/W)
static volatile __sfr __at(0x01) rSB;

// Serial I/O Control (R/W)
static volatile __sfr __at(0x02) rSC;

// Divider register (R/W)
static volatile __sfr __at(0x04) rDIV;

// Timer counter (R/W)
static volatile __sfr __at(0x05) rTIMA;

// Timer modulo (R/W)
static volatile __sfr __at(0x06) rTMA;

// Timer control (R/W)
static volatile __sfr __at(0x07) rTAC;

#define TACF_START 0b00000100
#define TACF_STOP 0b00000000
#define TACF_4KHZ 0b00000000
#define TACF_16KHZ 0b00000011
#define TACF_65KHZ 0b00000010
#define TACF_262KHZ 0b00000001


// Interrupt Flag (R/W)
static volatile __sfr __at(0x0F) rIF;


//
// AUD1SWEEP/NR10 ($FF10)
// Sweep register (R/W)
//
// Bit 6-4 - Sweep Time
// Bit 3   - Sweep Increase/Decrease
//           0: Addition    (frequency increases???)
//           1: Subtraction (frequency increases???)
// Bit 2-0 - Number of sweep shift (# 0-7)
// Sweep Time: (n*7.8ms)
//
static volatile __sfr __at(0x10) rNR10;
#define rAUD1SWEEP rNR10

#define AUD1SWEEP_UP 0b00000000
#define AUD1SWEEP_DOWN 0b00001000


//
// AUD1LEN/NR11 ($FF11)
// Sound length/Wave pattern duty (R/W)
//
// Bit 7-6 - Wave Pattern Duty (00:12.5% 01:25% 10:50% 11:75%)
// Bit 5-0 - Sound length data (# 0-63)
//
static volatile __sfr __at(0x11) rNR11;
#define rAUD1LEN rNR11


//
// AUD1ENV/NR12 ($FF12)
// Envelope (R/W)
//
// Bit 7-4 - Initial value of envelope
// Bit 3   - Envelope UP/DOWN
//           0: Decrease
//           1: Range of increase
// Bit 2-0 - Number of envelope sweep (# 0-7)
//
static volatile __sfr __at(0x12) rNR12;
#define rAUD1ENV rNR12


//
// AUD1LOW/NR13 ($FF13)
// Frequency low byte (W)
//
static volatile __sfr __at(0x13) rNR13;
#define rAUD1LOW rNR13


//
// AUD1HIGH/NR14 ($FF14)
// Frequency high byte (W)
//
// Bit 7   - Initial (when set, sound restarts)
// Bit 6   - Counter/consecutive selection
// Bit 2-0 - Frequency's higher 3 bits
//
static volatile __sfr __at(0x14) rNR14;
#define rAUD1HIGH rNR14


//
// AUD2LEN/NR21 ($FF16)
// Sound Length; Wave Pattern Duty (R/W)
//
// see AUD1LEN for info
//
static volatile __sfr __at(0x16) rNR21;
#define rAUD2LEN rNR21


//
// AUD2ENV/NR22 ($FF17)
// Envelope (R/W)
//
// see AUD1ENV for info
//
static volatile __sfr __at(0x17) rNR22;
#define rAUD2ENV rNR22


//
// AUD2LOW/NR23 ($FF18)
// Frequency low byte (W)
//
static volatile __sfr __at(0x18) rNR23;
#define rAUD2LOW rNR23


//
// AUD2HIGH/NR24 ($FF19)
// Frequency high byte (W)
//
// see AUD1HIGH for info
//
static volatile __sfr __at(0x19) rNR24;
#define rAUD2HIGH rNR24


//
// AUD3ENA/NR30 ($FF1A)
// Sound on/off (R/W)
//
// Bit 7   - Sound ON/OFF (1=ON,0=OFF)
//
static volatile __sfr __at(0x1A) rNR30;
#define rAUD3ENA rNR30


//
// AUD3LEN/NR31 ($FF1B)
// Sound length (R/W)
//
// Bit 7-0 - Sound length
//
static volatile __sfr __at(0x1B) rNR31;
#define rAUD3LEN rNR31


//
// AUD3LEVEL/NR32 ($FF1C)
// Select output level
//
// Bit 6-5 - Select output level
//           00: 0/1 (mute)
//           01: 1/1
//           10: 1/2
//           11: 1/4
//
static volatile __sfr __at(0x1C) rNR32;
#define rAUD3LEVEL rNR32


//
// AUD3LOW/NR33 ($FF1D)
// Frequency low byte (W)
//
// see AUD1LOW for info
//
static volatile __sfr __at(0x1D) rNR33;
#define rAUD3LOW rNR33


//
// AUD3HIGH/NR34 ($FF1E)
// Frequency high byte (W)
//
// see AUD1HIGH for info
//
static volatile __sfr __at(0x1E) rNR34;
#define rAUD3HIGH rNR34


//
// AUD4LEN/NR41 ($FF20)
// Sound length (R/W)
//
// Bit 5-0 - Sound length data (# 0-63)
//
static volatile __sfr __at(0x20) rNR41;
#define rAUD4LEN rNR41


//
// AUD4ENV/NR42 ($FF21)
// Envelope (R/W)
//
// see AUD1ENV for info
//
static volatile __sfr __at(0x21) rNR42;
#define rAUD4ENV rNR42


//
// AUD4POLY/NR43 ($FF22)
// Polynomial counter (R/W)
//
// Bit 7-4 - Selection of the shift clock frequency of the (scf)
//           polynomial counter (0000-1101)
//           freq=drf*1/2^scf (not sure)
// Bit 3 -   Selection of the polynomial counter's step
//           0: 15 steps
//           1: 7 steps
// Bit 2-0 - Selection of the dividing ratio of frequencies (drf)
//           000: f/4   001: f/8   010: f/16  011: f/24
//           100: f/32  101: f/40  110: f/48  111: f/56  (f=4.194304 Mhz)
//
static volatile __sfr __at(0x22) rNR43;
#define rAUD4POLY rNR43


//
// AUD4GO/NR44 ($FF23)
//
// Bit 7 -   Inital
// Bit 6 -   Counter/consecutive selection
//
static volatile __sfr __at(0x23) rNR44;
#define rAUD4GO rNR44


//
// AUDVOL/NR50 ($FF24)
// Channel control / ON-OFF / Volume (R/W)
//
// Bit 7   - Vin->SO2 ON/OFF (Vin??)
// Bit 6-4 - SO2 output level (volume) (# 0-7)
// Bit 3   - Vin->SO1 ON/OFF (Vin??)
// Bit 2-0 - SO1 output level (volume) (# 0-7)
//
static volatile __sfr __at(0x24) rNR50;
#define rAUDVOL rNR50

#define AUDVOL_VIN_LEFT 0b10000000 // SO2
#define AUDVOL_VIN_RIGHT 0b00001000 // SO1


//
// AUDTERM/NR51 ($FF25)
// Selection of Sound output terminal (R/W)
//
// Bit 7   - Output sound 4 to SO2 terminal
// Bit 6   - Output sound 3 to SO2 terminal
// Bit 5   - Output sound 2 to SO2 terminal
// Bit 4   - Output sound 1 to SO2 terminal
// Bit 3   - Output sound 4 to SO1 terminal
// Bit 2   - Output sound 3 to SO1 terminal
// Bit 1   - Output sound 2 to SO1 terminal
// Bit 0   - Output sound 0 to SO1 terminal
//
static volatile __sfr __at(0x25) rNR51;
#define rAUDTERM rNR51

// SO2
#define AUDTERM_4_LEFT 0b10000000
#define AUDTERM_3_LEFT 0b01000000
#define AUDTERM_2_LEFT 0b00100000
#define AUDTERM_1_LEFT 0b00010000
// SO1
#define AUDTERM_4_RIGHT 0b00001000
#define AUDTERM_3_RIGHT 0b00000100
#define AUDTERM_2_RIGHT 0b00000010
#define AUDTERM_1_RIGHT 0b00000001


//
// AUDENA/NR52 ($FF26)
// Sound on/off (R/W)
//
// Bit 7   - All sound on/off (sets all audio regs to 0!)
// Bit 3   - Sound 4 ON flag (read only)
// Bit 2   - Sound 3 ON flag (read only)
// Bit 1   - Sound 2 ON flag (read only)
// Bit 0   - Sound 1 ON flag (read only)
//
static volatile __sfr __at(0x26) rNR52;
#define rAUDENA rNR52

#define AUDENA_ON 0b10000000
#define AUDENA_OFF 0b00000000 // sets all audio regs to 0!


//
// LCDC ($FF40)
// LCD Control (R/W)
//
static volatile __sfr __at(0x40) rLCDC;

#define LCDCF_OFF 0b00000000 // LCD Control Operation
#define LCDCF_ON 0b10000000 // LCD Control Operation
#define LCDCF_WIN9800 0b00000000 // Window Tile Map Display Select
#define LCDCF_WIN9C00 0b01000000 // Window Tile Map Display Select
#define LCDCF_WINOFF 0b00000000 // Window Display
#define LCDCF_WINON 0b00100000 // Window Display
#define LCDCF_BG8800 0b00000000 // BG & Window Tile Data Select
#define LCDCF_BG8000 0b00010000 // BG & Window Tile Data Select
#define LCDCF_BG9800 0b00000000 // BG Tile Map Display Select
#define LCDCF_BG9C00 0b00001000 // BG Tile Map Display Select
#define LCDCF_OBJ8 0b00000000 // OBJ Construction
#define LCDCF_OBJ16 0b00000100 // OBJ Construction
#define LCDCF_OBJOFF 0b00000000 // OBJ Display
#define LCDCF_OBJON 0b00000010 // OBJ Display
#define LCDCF_BGOFF 0b00000000 // BG Display
#define LCDCF_BGON 0b00000001 // BG Display
// "Window Character Data Select" follows BG


//
// STAT ($FF41)
// LCDC Status   (R/W)
//
static volatile __sfr __at(0x41) rSTAT;

#define STATF_LYC 0b01000000 // LYC=LY Coincidence (Selectable)
#define STATF_MODE10 0b00100000 // Mode 10
#define STATF_MODE01 0b00010000 // Mode 01 (V-Blank)
#define STATF_MODE00 0b00001000 // Mode 00 (H-Blank)
#define STATF_LYCF 0b00000100 // Coincidence Flag
#define STATF_HBL 0b00000000 // H-Blank
#define STATF_VBL 0b00000001 // V-Blank
#define STATF_OAM 0b00000010 // OAM-RAM is used by system
#define STATF_LCD 0b00000011 // Both OAM and VRAM used by system
#define STATF_BUSY 0b00000010 // When set, VRAM access is unsafe


//
// SCY ($FF42)
// Scroll Y (R/W)
//
static volatile __sfr __at(0x42) rSCY;


//
// SCX ($FF43)
// Scroll X (R/W)
//
static volatile __sfr __at(0x43) rSCX;


//
// LY ($FF44)
// LCDC Y-Coordinate (R)
//
// Values range from 0->153. 144->153 is the VBlank period.
//
static volatile __sfr __at(0x44) rLY;


//
// LYC ($FF45)
// LY Compare (R/W)
//
// When LY==LYC, STATF_LYCF will be set in STAT
//
static volatile __sfr __at(0x45) rLYC;


//
// DMA ($FF46)
// DMA Transfer and Start Address (W)
//
static volatile __sfr __at(0x46) rDMA;


//
// BGP ($FF47)
// BG Palette Data (W)
//
// Bit 7-6 - Intensity for %11
// Bit 5-4 - Intensity for %10
// Bit 3-2 - Intensity for %01
// Bit 1-0 - Intensity for %00
//
static volatile __sfr __at(0x47) rBGP;


//
// OBP0 ($FF48)
// Object Palette 0 Data (W)
//
// See BGP for info
//
static volatile __sfr __at(0x48) rOBP0;


//
// OBP1 ($FF49)
// Object Palette 1 Data (W)
//
// See BGP for info
//
static volatile __sfr __at(0x49) rOBP1;


//
// WY ($FF4A)
// Window Y Position (R/W)
//
// 0 <= WY <= 143
// When WY = 0, the window is displayed from the top edge of the LCD screen.
//
static volatile __sfr __at(0x4A) rWY;


//
// WX ($FF4B)
// Window X Position (R/W)
//
// 7 <= WX <= 166
// When WX = 7, the window is displayed from the left edge of the LCD screen.
// Values of 0-6 and 166 are unreliable due to hardware bugs.
//
static volatile __sfr __at(0x4B) rWX;


//
// SPEED ($FF4D)
// Select CPU Speed (R/W)
//
static volatile __sfr __at(0x4D) rKEY1;
#define rSPD  rKEY1

#define KEY1F_DBLSPEED 0b10000000 // 0=Normal Speed, 1=Double Speed (R)
#define KEY1F_PREPARE 0b00000001 // 0=No, 1=Prepare (R/W)


//
// VBK ($FF4F)
// Select Video RAM Bank (R/W)
//
// Bit 0 - Bank Specification (0: Specify Bank 0; 1: Specify Bank 1)
//
static volatile __sfr __at(0x4F) rVBK;


//
// HDMA1 ($FF51)
// High byte for Horizontal Blanking/General Purpose DMA source address (W)
// CGB Mode Only
//
static volatile __sfr __at(0x51) rHDMA1;


//
// HDMA2 ($FF52)
// Low byte for Horizontal Blanking/General Purpose DMA source address (W)
// CGB Mode Only
//
static volatile __sfr __at(0x52) rHDMA2;


//
// HDMA3 ($FF53)
// High byte for Horizontal Blanking/General Purpose DMA destination address (W)
// CGB Mode Only
//
static volatile __sfr __at(0x53) rHDMA3;


//
// HDMA4 ($FF54)
// Low byte for Horizontal Blanking/General Purpose DMA destination address (W)
// CGB Mode Only
//
static volatile __sfr __at(0x54) rHDMA4;


//
// HDMA5 ($FF55)
// Transfer length (in tiles minus 1)/mode/start for Horizontal Blanking, General Purpose DMA (R/W)
// CGB Mode Only
//
static volatile __sfr __at(0x55) rHDMA5;

#define HDMA5F_MODE_GP 0b00000000 // General Purpose DMA (W)
#define HDMA5F_MODE_HBL 0b10000000 // HBlank DMA (W)

// Once DMA has started, use HDMA5F_BUSY to check when the transfer is complete
#define HDMA5F_BUSY 0b10000000 // 0=Busy (DMA still in progress), 1=Transfer complete (R)


//
// RP ($FF56)
// Infrared Communications Port (R/W)
// CGB Mode Only
//
static volatile __sfr __at(0x56) rRP;

#define RPF_ENREAD 0b11000000
#define RPF_DATAIN 0b00000010 // 0=Receiving IR Signal, 1=Normal
#define RPF_WRITE_HI 0b00000001
#define RPF_WRITE_LO 0b00000000


//
// BCPS ($FF68)
// Background Color Palette Specification (R/W)
//
static volatile __sfr __at(0x68) rBCPS;

#define BCPSF_AUTOINC 0b10000000 // Auto Increment (0=Disabled, 1=Increment after Writing)


//
// BCPD ($FF69)
// Background Color Palette Data (R/W)
//
static volatile __sfr __at(0x69) rBCPD;


//
// OCPS ($FF6A)
// Object Color Palette Specification (R/W)
//
static volatile __sfr __at(0x6A) rOCPS;

#define OCPSF_AUTOINC 0b10000000 // Auto Increment (0=Disabled, 1=Increment after Writing)


//
// OCPD ($FF6B)
// Object Color Palette Data (R/W)
//
static volatile __sfr __at(0x6B) rOCPD;


//
// SMBK/SVBK ($FF70)
// Select Main RAM Bank (R/W)
//
// Bit 2-0 - Bank Specification (0,1: Specify Bank 1; 2-7: Specify Banks 2-7)
//
static volatile __sfr __at(0x70) rSVBK;
#define rSMBK rSVBK


//
// PCM12 ($FF76)
// Sound channel 1&2 PCM amplitude (R)
//
// Bit 7-4 - Copy of sound channel 2's PCM amplitude
// Bit 3-0 - Copy of sound channel 1's PCM amplitude
//
static volatile __sfr __at(0x76) rPCM12;


//
// PCM34 ($FF77)
// Sound channel 3&4 PCM amplitude (R)
//
// Bit 7-4 - Copy of sound channel 4's PCM amplitude
// Bit 3-0 - Copy of sound channel 3's PCM amplitude
//
static volatile __sfr __at(0x77) rPCM34;


//
// IE ($FFFF)
// Interrupt Enable (R/W)
//
static volatile __sfr __at(0xFF) rIE;

#define IEF_HILO 0b00010000 // Transition from High to Low of Pin number P10-P13
#define IEF_SERIAL 0b00001000 // Serial I/O transfer end
#define IEF_TIMER 0b00000100 // Timer Overflow
#define IEF_LCDC 0b00000010 // LCDC (see STAT)
#define IEF_VBLANK 0b00000001 // V-Blank


/***************************************************************************
 *
 * Flags common to multiple sound channels
 *
 ***************************************************************************/

//
// Square wave duty cycle
//
// Can be used with AUD1LEN and AUD2LEN
// See AUD1LEN for more info
//
#define AUDLEN_DUTY_12_5 0b00000000 // 12.5%
#define AUDLEN_DUTY_25 0b01000000 // 25%
#define AUDLEN_DUTY_50 0b10000000 // 50%
#define AUDLEN_DUTY_75 0b11000000 // 75%


//
// Audio envelope flags
//
// Can be used with AUD1ENV, AUD2ENV, AUD4ENV
// See AUD1ENV for more info
//
#define AUDENV_UP 0b00001000
#define AUDENV_DOWN 0b00000000


//
// Audio trigger flags
//
// Can be used with AUD1HIGH, AUD2HIGH, AUD3HIGH
// See AUD1HIGH for more info
//

#define AUDHIGH_RESTART 0b10000000
#define AUDHIGH_LENGTH_ON 0b01000000
#define AUDHIGH_LENGTH_OFF 0b00000000

#define HALT() __asm__("halt")
#define DISABLE_INTERRUPTS() __asm__("di")
#define ENABLE_INTERRUPTS() __asm__("ei")

#endif
