#ifndef GBSDK_HARDWARE_H
#define GBSDK_HARDWARE_H

// We need to disable warning 182, as SDCC 4.1.0 incorrectly thinks registers are in 0x0000 to 0x00FF range.
//  putting the registers in the 0x0000-0x00FF range works most of the time, but sometimes causes incorrect
//  code generation.
#pragma disable_warning 182

// Register for reading joy pad info. (R/W)
static volatile __sfr __at(0xFF00) rP1;

#define P1_5 0b00100000 // P15 out port, set to 0 to get buttons
#define P1_4 0b00010000 // P14 out port, set to 0 to get dpad
#define P1_3 0b00001000 // P13 in port
#define P1_2 0b00000100 // P12 in port
#define P1_1 0b00000010 // P11 in port
#define P1_0 0b00000001 // P10 in port

#define P1_GET_DPAD P1_5
#define P1_GET_BTN  P1_4
#define P1_GET_NONE (P1_4 | P1_5)

// Serial Transfer Data (R/W)
static volatile __sfr __at(0xFF01) rSB;

// Serial I/O Control (R/W)
static volatile __sfr __at(0xFF02) rSC;

#define SCF_START 0b10000000 // Transfer Start Flag (1=Transfer in progress, or requested)
#define SCF_SPEED 0b00000010 // Clock Speed (0=Normal, 1=Fast) ** CGB Mode Only **
#define SCF_SOURCE 0b00000001 // Shift Clock (0=External Clock, 1=Internal Clock)

#define SCB_START 7
#define SCB_SPEED 1
#define SCB_SOURCE 0

// Divider register (R/W)
static volatile __sfr __at(0xFF04) rDIV;

// Timer counter (R/W)
static volatile __sfr __at(0xFF05) rTIMA;

// Timer modulo (R/W)
static volatile __sfr __at(0xFF06) rTMA;

// Timer control (R/W)
static volatile __sfr __at(0xFF07) rTAC;

#define TAC_START 0b00000100
#define TAC_STOP 0b00000000
#define TAC_4KHZ 0b00000000
#define TAC_16KHZ 0b00000011
#define TAC_65KHZ 0b00000010
#define TAC_262KHZ 0b00000001

// Interrupt Flag (R/W)
static volatile __sfr __at(0xFF0F) rIF;

// AUD1SWEEP/NR10 ($FF10)
// Sweep register (R/W)
//
// Bit 6-4 - Sweep Time
// Bit 3   - Sweep Increase/Decrease
//           0: Addition    (frequency increases???)
//           1: Subtraction (frequency increases???)
// Bit 2-0 - Number of sweep shift (# 0-7)
// Sweep Time: (n*7.8ms)
static volatile __sfr __at(0xFF10) rNR10;
#define rAUD1SWEEP rNR10

#define AUD1SWEEP_UP 0b00000000
#define AUD1SWEEP_DOWN 0b00001000

// AUD1LEN/NR11 ($FF11)
// Sound length/Wave pattern duty (R/W)
//
// Bit 7-6 - Wave Pattern Duty (00:12.5% 01:25% 10:50% 11:75%)
// Bit 5-0 - Sound length data (# 0-63)
static volatile __sfr __at(0xFF11) rNR11;
#define rAUD1LEN rNR11

// AUD1ENV/NR12 ($FF12)
// Envelope (R/W)
//
// Bit 7-4 - Initial value of envelope
// Bit 3   - Envelope UP/DOWN
//           0: Decrease
//           1: Range of increase
// Bit 2-0 - Number of envelope sweep (# 0-7)
static volatile __sfr __at(0xFF12) rNR12;
#define rAUD1ENV rNR12

// AUD1LOW/NR13 ($FF13)
// Frequency low byte (W)
static volatile __sfr __at(0xFF13) rNR13;
#define rAUD1LOW rNR13

// AUD1HIGH/NR14 ($FF14)
// Frequency high byte (W)
//
// Bit 7   - Initial (when set, sound restarts)
// Bit 6   - Counter/consecutive selection
// Bit 2-0 - Frequency's higher 3 bits
static volatile __sfr __at(0xFF14) rNR14;
#define rAUD1HIGH rNR14

// AUD2LEN/NR21 ($FF16)
// Sound Length; Wave Pattern Duty (R/W)
//
// see AUD1LEN for info
static volatile __sfr __at(0xFF16) rNR21;
#define rAUD2LEN rNR21

// AUD2ENV/NR22 ($FF17)
// Envelope (R/W)
//
// see AUD1ENV for info
static volatile __sfr __at(0xFF17) rNR22;
#define rAUD2ENV rNR22

// AUD2LOW/NR23 ($FF18)
// Frequency low byte (W)
static volatile __sfr __at(0xFF18) rNR23;
#define rAUD2LOW rNR23

// AUD2HIGH/NR24 ($FF19)
// Frequency high byte (W)
//
// see AUD1HIGH for info
static volatile __sfr __at(0xFF19) rNR24;
#define rAUD2HIGH rNR24

// AUD3ENA/NR30 ($FF1A)
// Sound on/off (R/W)
//
// Bit 7   - Sound ON/OFF (1=ON,0=OFF)
static volatile __sfr __at(0xFF1A) rNR30;
#define rAUD3ENA rNR30

#define AUD3ENA_OFF 0b00000000
#define AUD3ENA_ON 0b10000000

// AUD3LEN/NR31 ($FF1B)
// Sound length (R/W)
//
// Bit 7-0 - Sound length
static volatile __sfr __at(0xFF1B) rNR31;
#define rAUD3LEN rNR31

// AUD3LEVEL/NR32 ($FF1C)
// Select output level
//
// Bit 6-5 - Select output level
//           00: 0/1 (mute)
//           01: 1/1
//           10: 1/2
//           11: 1/4
static volatile __sfr __at(0xFF1C) rNR32;
#define rAUD3LEVEL rNR32

#define AUD3LEVEL_MUTE 0b00000000
#define AUD3LEVEL_100  0b00100000
#define AUD3LEVEL_50   0b01000000
#define AUD3LEVEL_25   0b01100000

// AUD3LOW/NR33 ($FF1D)
// Frequency low byte (W)
//
// see AUD1LOW for info
static volatile __sfr __at(0xFF1D) rNR33;
#define rAUD3LOW rNR33

// AUD3HIGH/NR34 ($FF1E)
// Frequency high byte (W)
//
// see AUD1HIGH for info
static volatile __sfr __at(0xFF1E) rNR34;
#define rAUD3HIGH rNR34

// AUD4LEN/NR41 ($FF20)
// Sound length (R/W)
//
// Bit 5-0 - Sound length data (# 0-63)
static volatile __sfr __at(0xFF20) rNR41;
#define rAUD4LEN rNR41

// AUD4ENV/NR42 ($FF21)
// Envelope (R/W)
//
// see AUD1ENV for info
static volatile __sfr __at(0xFF21) rNR42;
#define rAUD4ENV rNR42

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
static volatile __sfr __at(0xFF22) rNR43;
#define rAUD4POLY rNR43

#define AUD4POLY_15STEP 0b00000000
#define AUD4POLY_7STEP 0b00001000

// AUD4GO/NR44 ($FF23)
//
// Bit 7 -   Initial (when set, sound restarts)
// Bit 6 -   Counter/consecutive selection
static volatile __sfr __at(0xFF23) rNR44;
#define rAUD4GO rNR44

// AUDVOL/NR50 ($FF24)
// Channel control / ON-OFF / Volume (R/W)
//
// Bit 7   - Vin->SO2 ON/OFF (left)
// Bit 6-4 - SO2 output level (left speaker) (# 0-7)
// Bit 3   - Vin->SO1 ON/OFF (right)
// Bit 2-0 - SO1 output level (right speaker) (# 0-7)
static volatile __sfr __at(0xFF24) rNR50;
#define rAUDVOL rNR50

#define AUDVOL_VIN_LEFT 0b10000000 // SO2
#define AUDVOL_VIN_RIGHT 0b00001000 // SO1

// AUDTERM/NR51 ($FF25)
// Selection of Sound output terminal (R/W)
//
// Bit 7   - Output channel 4 to SO2 terminal (left)
// Bit 6   - Output channel 3 to SO2 terminal (left)
// Bit 5   - Output channel 2 to SO2 terminal (left)
// Bit 4   - Output channel 1 to SO2 terminal (left)
// Bit 3   - Output channel 4 to SO1 terminal (right)
// Bit 2   - Output channel 3 to SO1 terminal (right)
// Bit 1   - Output channel 2 to SO1 terminal (right)
// Bit 0   - Output channel 1 to SO1 terminal (right)
static volatile __sfr __at(0xFF25) rNR51;
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

// AUDENA/NR52 ($FF26)
// Sound on/off (R/W)
//
// Bit 7   - All sound on/off (sets all audio regs to 0!)
// Bit 3   - Sound 4 ON flag (read only)
// Bit 2   - Sound 3 ON flag (read only)
// Bit 1   - Sound 2 ON flag (read only)
// Bit 0   - Sound 1 ON flag (read only)
static volatile __sfr __at(0xFF26) rNR52;
#define rAUDENA rNR52

#define AUDENA_ON 0b10000000
#define AUDENA_OFF 0b00000000 // sets all audio regs to 0!

// LCDC ($FF40)
// LCD Control (R/W)
static volatile __sfr __at(0xFF40) rLCDC;

#define LCDC_OFF 0b00000000 // LCD Control Operation
#define LCDC_ON 0b10000000 // LCD Control Operation
#define LCDC_WIN9800 0b00000000 // Window Tile Map Display Select
#define LCDC_WIN9C00 0b01000000 // Window Tile Map Display Select
#define LCDC_WINOFF 0b00000000 // Window Display
#define LCDC_WINON 0b00100000 // Window Display
#define LCDC_BG8800 0b00000000 // BG & Window Tile Data Select
#define LCDC_BG8000 0b00010000 // BG & Window Tile Data Select
#define LCDC_BG9800 0b00000000 // BG Tile Map Display Select
#define LCDC_BG9C00 0b00001000 // BG Tile Map Display Select
#define LCDC_OBJ8 0b00000000 // OBJ Construction
#define LCDC_OBJ16 0b00000100 // OBJ Construction
#define LCDC_OBJOFF 0b00000000 // OBJ Display
#define LCDC_OBJON 0b00000010 // OBJ Display
#define LCDC_BGOFF 0b00000000 // BG Display
#define LCDC_BGON 0b00000001 // BG Display

// STAT ($FF41)
// LCDC Status   (R/W)
static volatile __sfr __at(0xFF41) rSTAT;

#define STAT_LYC 0b01000000 // LYC=LY Coincidence (Selectable)
#define STAT_MODE10 0b00100000 // Mode 10
#define STAT_MODE01 0b00010000 // Mode 01 (V-Blank)
#define STAT_MODE00 0b00001000 // Mode 00 (H-Blank)
#define STAT_LYCF 0b00000100 // Coincidence Flag
#define STAT_HBL 0b00000000 // H-Blank
#define STAT_VBL 0b00000001 // V-Blank
#define STAT_OAM 0b00000010 // OAM-RAM is used by system
#define STAT_LCD 0b00000011 // Both OAM and VRAM used by system
#define STAT_BUSY 0b00000010 // When set, VRAM access is unsafe

#define STATB_LYC 6
#define STATB_MODE10 5
#define STATB_MODE01 4
#define STATB_MODE00 3
#define STATB_LYCF 2
#define STATB_BUSY 1

// SCY ($FF42)
// Scroll Y (R/W)
static volatile __sfr __at(0xFF42) rSCY;

// SCX ($FF43)
// Scroll X (R/W)
static volatile __sfr __at(0xFF43) rSCX;

// LY ($FF44)
// LCDC Y-Coordinate (R)
//
// Values range from 0->153. 144->153 is the VBlank period.
static volatile __sfr __at(0xFF44) rLY;

// LYC ($FF45)
// LY Compare (R/W)
//
// When LY==LYC, STATF_LYCF will be set in STAT
static volatile __sfr __at(0xFF45) rLYC;

// DMA ($FF46)
// DMA Transfer and Start Address (W)
static volatile __sfr __at(0xFF46) rDMA;

// BGP ($FF47)
// BG Palette Data (W)
//
// Bit 7-6 - Intensity for %11
// Bit 5-4 - Intensity for %10
// Bit 3-2 - Intensity for %01
// Bit 1-0 - Intensity for %00
static volatile __sfr __at(0xFF47) rBGP;

// OBP0 ($FF48)
// Object Palette 0 Data (W)
//
// See BGP for info
static volatile __sfr __at(0xFF48) rOBP0;

// OBP1 ($FF49)
// Object Palette 1 Data (W)
//
// See BGP for info
static volatile __sfr __at(0xFF49) rOBP1;

// WY ($FF4A)
// Window Y Position (R/W)
//
// 0 <= WY <= 143
// When WY = 0, the window is displayed from the top edge of the LCD screen.
static volatile __sfr __at(0xFF4A) rWY;

// WX ($FF4B)
// Window X Position (R/W)
//
// 7 <= WX <= 166
// When WX = 7, the window is displayed from the left edge of the LCD screen.
// Values of 0-6 and 166 are unreliable due to hardware bugs.
static volatile __sfr __at(0xFF4B) rWX;

#define WX_OFS 7 // add this to a screen position to get a WX position


#if CGB
// SPEED ($FF4D)
// Select CPU Speed (R/W)
static volatile __sfr __at(0xFF4D) rKEY1;
#define rSPD  rKEY1

#define KEY1_DBLSPEED 0b10000000 // 0=Normal Speed, 1=Double Speed (R)
#define KEY1_PREPARE 0b00000001 // 0=No, 1=Prepare (R/W)

// VBK ($FF4F)
// Select Video RAM Bank (R/W)
//
// Bit 0 - Bank Specification (0: Specify Bank 0; 1: Specify Bank 1)
static volatile __sfr __at(0xFF4F) rVBK;

// HDMA1 ($FF51)
// High byte for Horizontal Blanking/General Purpose DMA source address (W)
static volatile __sfr __at(0xFF51) rHDMA1;

// HDMA2 ($FF52)
// Low byte for Horizontal Blanking/General Purpose DMA source address (W)
static volatile __sfr __at(0xFF52) rHDMA2;

// HDMA3 ($FF53)
// High byte for Horizontal Blanking/General Purpose DMA destination address (W)
static volatile __sfr __at(0xFF53) rHDMA3;

// HDMA4 ($FF54)
// Low byte for Horizontal Blanking/General Purpose DMA destination address (W)
static volatile __sfr __at(0xFF54) rHDMA4;

// HDMA5 ($FF55)
// Transfer length (in tiles minus 1)/mode/start for Horizontal Blanking, General Purpose DMA (R/W)
static volatile __sfr __at(0xFF55) rHDMA5;

#define HDMA5_MODE_GP 0b00000000 // General Purpose DMA (W)
#define HDMA5_MODE_HBL 0b10000000 // HBlank DMA (W)

// Once DMA has started, use HDMA5F_BUSY to check when the transfer is complete
#define HDMA5_BUSY 0b10000000 // 0=Busy (DMA still in progress), 1=Transfer complete (R)

// RP ($FF56)
// Infrared Communications Port (R/W)
static volatile __sfr __at(0xFF56) rRP;

#define RP_ENREAD 0b11000000
#define RP_DATAIN 0b00000010 // 0=Receiving IR Signal, 1=Normal
#define RP_WRITE_HI 0b00000001
#define RP_WRITE_LO 0b00000000

// BCPS ($FF68)
// Background Color Palette Specification (R/W)
static volatile __sfr __at(0xFF68) rBCPS;
#define BCPS_AUTOINC 0b10000000 // Auto Increment (0=Disabled, 1=Increment after Writing)

// BCPD ($FF69)
// Background Color Palette Data (R/W)
static volatile __sfr __at(0xFF69) rBCPD;

// OCPS ($FF6A)
// Object Color Palette Specification (R/W)
static volatile __sfr __at(0xFF6A) rOCPS;
#define OCPS_AUTOINC 0b10000000 // Auto Increment (0=Disabled, 1=Increment after Writing)

// OCPD ($FF6B)
// Object Color Palette Data (R/W)
static volatile __sfr __at(0xFF6B) rOCPD;

// SMBK/SVBK ($FF70)
// Select Main RAM Bank (R/W)
//
// Bit 2-0 - Bank Specification (0,1: Specify Bank 1; 2-7: Specify Banks 2-7)
static volatile __sfr __at(0xFF70) rSVBK;
#define rSMBK rSVBK

// PCM12 ($FF76)
// Sound channel 1&2 PCM amplitude (R)
//
// Bit 7-4 - Copy of sound channel 2's PCM amplitude
// Bit 3-0 - Copy of sound channel 1's PCM amplitude
static volatile __sfr __at(0xFF76) rPCM12;

// PCM34 ($FF77)
// Sound channel 3&4 PCM amplitude (R)
//
// Bit 7-4 - Copy of sound channel 4's PCM amplitude
// Bit 3-0 - Copy of sound channel 3's PCM amplitude
static volatile __sfr __at(0xFF77) rPCM34;

#endif //CGB

// IE ($FFFF)
// Interrupt Enable (R/W)
static volatile __sfr __at(0xFFFF) rIE;

#define IE_HILO 0b00010000 // Transition from High to Low of Pin number P10-P13
#define IE_SERIAL 0b00001000 // Serial I/O transfer end
#define IE_TIMER 0b00000100 // Timer Overflow
#define IE_STAT 0b00000010 // STAT
#define IE_VBLANK 0b00000001 // V-Blank

#define IEB_HILO 4
#define IEB_SERIAL 3
#define IEB_TIMER 2
#define IEB_STAT 1
#define IEB_VBLANK 0


/***************************************************************************
 *
 * Flags common to multiple sound channels
 *
 ***************************************************************************/

// Square wave duty cycle
//
// Can be used with AUD1LEN and AUD2LEN
// See AUD1LEN for more info
#define AUDLEN_DUTY_12_5 0b00000000 // 12.5%
#define AUDLEN_DUTY_25 0b01000000 // 25%
#define AUDLEN_DUTY_50 0b10000000 // 50%
#define AUDLEN_DUTY_75 0b11000000 // 75%

// Audio envelope flags
//
// Can be used with AUD1ENV, AUD2ENV, AUD4ENV
// See AUD1ENV for more info
#define AUDENV_UP 0b00001000
#define AUDENV_DOWN 0b00000000

// Audio trigger flags
//
// Can be used with AUD1HIGH, AUD2HIGH, AUD3HIGH
// See AUD1HIGH for more info
#define AUDHIGH_RESTART 0b10000000
#define AUDHIGH_LENGTH_ON 0b01000000
#define AUDHIGH_LENGTH_OFF 0b00000000

// Shared bits between the OAM attributes and the CGB background attributes.
#define ATTR_PRI     0b10000000
#define ATTR_YFLIP   0b01000000
#define ATTR_XFLIP   0b00100000
#define ATTR_PAL0    0b00000000
#define ATTR_PAL1    0b00010000
#if CGB
#define ATTR_BANK0   0b00000000
#define ATTR_BANK1   0b00001000
#define ATTR_PALMASK 0b00000111
#endif

// Deprecated constants. Please avoid using.
#define IE_LCDC 0b00000010

#endif
