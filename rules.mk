.PHONY: all clean

# SDCC renamed the `gbz80` arch to `sm83` in 4.2.0
ARCH := sm83
SDCC_VERSTRING := $(shell sdcc --version)
ifeq ($(findstring sm83,$(SDCC_VERSTRING)),)
$(info $(SDCC_VERSTRING))
$(error Installed SDCC version is unsupported. Minimum supported version is 4.2.0)
endif

MYDIR     := $(dir $(lastword $(MAKEFILE_LIST)))

ifndef PROJECT_NAME
$(error PROJECT_NAME is not set to the name of your rom.)
endif
ifndef MBC
$(error MBC is not set. Should be set to the MBC name or value you want. Example "MBC5+RAM+BATTERY")
endif
ifndef TARGETS
$(error TARGETS is not set. Should be a combination of DMG SGB CGB)
endif
ifneq ($(filter-out DMG SGB CGB,$(TARGETS)),)
$(error TARGETS should be a combination of DMG SGB CGB, unknown: $(filter-out DMG SGB CGB,$(TARGETS)))
endif

SRC       := $(shell find src/ -type f -name '*.c') $(shell find $(MYDIR)/src/ -type f -name '*.c')
ASM       := $(shell find src/ -type f -name '*.asm') $(shell find $(MYDIR)/src/ -type f -name '*.asm')

# Which files do we use from the sdcc libc
LIBC    := _memset.c $(ARCH)/memcpy.s
LIBC    += _divuchar.c _divschar.c _muluchar.c _mulschar.c _modschar.c _moduchar.c
LIBC    += _divuint.c _divsint.c _mulint.c _modsint.c _moduint.c
# the 32 bit functions use 10% of ROM0, so do not include them
#LIBC    += _divulong.c _divslong.c _mullong.c _modslong.c _modulong.c
LIBC_PATH := $(subst \,/,$(shell sdcc -m$(ARCH) --print-search-dirs | grep $(ARCH) | tail -n 1))/../src

ifneq (1,$(words [$(LIBC_PATH)]))
$(error "your environment or sdcc is installed in a path with spaces in it, this is not allowed, as it will break sdcc")
endif

Q ?= @

BUILD    := _build
TOOLS    := $(MYDIR)/tools
OBJS     := $(patsubst %, $(BUILD)/%.o, $(ASM) $(SRC)) $(patsubst %, $(BUILD)/libc/%.o, $(LIBC)) $(BUILD)/gsinit.end.o

CFLAGS   := -m$(ARCH) -Isrc/ -I$(MYDIR)/inc --max-allocs-per-node 25000
ASFLAGS  := -isrc/ -i$(MYDIR)/inc -i$(BUILD)/assets/ -Wall
LDFLAGS  := --pad 0xFF --wramx
FIXFLAGS := --validate --pad-value 0xFF --title "$(PROJECT_NAME)" --mbc-type "$(MBC)" -l 0x33
ROM_EXTENSION := gb
# Replace spaces with underscores in the project name.
PROJECT_NAME := $(subst $() $(),_,$(PROJECT_NAME))

ifeq ($(filter CGB,$(TARGETS)),) # Not targeting CGB, so disable CGB features
	CFLAGS  += -DCGB=0
	ASFLAGS += -DCGB=0
	LDFLAGS += --dmg
else
	CFLAGS  += -DCGB=1
	ASFLAGS += -DCGB=1
	ifeq ($(filter DMG,$(TARGETS))$(filter SGB,$(TARGETS)),) # Check if not targeting both CGB and DMG
		FIXFLAGS += --color-only
	else
		FIXFLAGS += --color-compatible
	endif
    ROM_EXTENSION := gbc
endif
ifeq ($(filter SGB,$(TARGETS)),) # Not targeting SGB, so disable SGB features
	CFLAGS  += -DSGB=0
	ASFLAGS += -DSGB=0
else # Targeting SGB as well
	CFLAGS  += -DSGB=1
	ASFLAGS += -DSGB=1
	FIXFLAGS += --sgb-compatible
endif
ifneq ($(findstring RAM,$(MBC)),)
	FIXFLAGS += --ram-size 2
endif

all: $(PROJECT_NAME).$(ROM_EXTENSION)

# Rules to make c files
$(BUILD)/%.c.as: %.c
	@echo Compiling $<
	@mkdir -p $(dir $@)
	$(Q)sdcc $(CFLAGS) -S $< -o $@ -Wp "-MQ $@ -MD $(@:.as=.as.d)"
-include $(patsubst %.c, $(BUILD)/%.c.as.d, $(SRC))

$(BUILD)/libc/%.c.as: $(LIBC_PATH)/%.c
	@echo Compiling $<
	@mkdir -p $(dir $@)
	$(Q)sdcc $(CFLAGS) -S $< -o $@

$(BUILD)/%.c.asm: $(BUILD)/%.c.as $(TOOLS)/asmconvert.py
	$(Q)python3 $(TOOLS)/asmconvert.py $(notdir $<) < $< > $@

$(BUILD)/%.c.asm.d: $(BUILD)/%.c.asm
	@mkdir -p $(dir $@)
	$(Q)rgbasm $(ASFLAGS) $< -M $@ -MT $(@:.asm.d=.o) -MT $@ -MG
#	rgbds dependency generation is broken, as it stops after the first missing file. so list all incbins always
	$(Q)cat $< | grep -i '^ *INCBIN' | sed -E 's/ *incbin *"([^"]*)"/$(subst /,\/,$(@:.asm.d=.o)): \1/gI' >> $@
-include $(patsubst %.c, $(BUILD)/%.c.asm.d, $(SRC))

$(BUILD)/%.c.o: $(BUILD)/%.c.asm $(BUILD)/%.c.asm.d
	@echo "Assembling (c)" $<
	@mkdir -p $(dir $@)
	$(Q)rgbasm $(ASFLAGS) $< -o $@

# Rules to build libc asm files
$(BUILD)/libc/%.s.asm: $(LIBC_PATH)/%.s $(TOOLS)/asmconvert.py
	@mkdir -p $(dir $@)
	$(Q)python3 $(TOOLS)/asmconvert.py $(notdir $<) < $< > $@

$(BUILD)/libc/%.s.o: $(BUILD)/libc/%.s.asm
	@echo Assembling $<
	@mkdir -p $(dir $@)
	$(Q)rgbasm $(ASFLAGS) $< -o $@

# Rules to build project asm files
$(BUILD)/%.asm.d: %.asm
	@mkdir -p $(dir $@)
	$(Q)rgbasm $(ASFLAGS) $< -M $@ -MT $(@:.d=.o) -MT $@ -MG
#	rgbds dependency generation is broken, as it stops after the first missing file. so list all incbins always
	$(Q)cat $< | grep -i '^ *INCBIN' | sed -E 's/incbin "([^"]*)"/$(subst /,\/,$(@:.d=.o)): \1/gI' >> $@

$(BUILD)/%.asm.o: %.asm $(BUILD)/%.asm.d
	@echo Assembling $<
	@mkdir -p $(dir $@)
	$(Q)rgbasm $(ASFLAGS) $< -o $@
-include $(patsubst %.asm, $(BUILD)/%.asm.d, $(ASM))

# Rule to build the final rom
$(PROJECT_NAME).$(ROM_EXTENSION) $(PROJECT_NAME).map $(PROJECT_NAME).sym: $(OBJS)
	@echo Linking $@
	$(Q)rgblink $(LDFLAGS) $^ -o $@ -m $(basename $@).map -n $(basename $@).sym
	$(Q)rgbfix $(FIXFLAGS) $@
	@python3 $(TOOLS)/romspace.py $(basename $@).map

# Asset related rules
$(BUILD)/assets/%.2bpp: assets/%.png
	@echo Converting $<
	@mkdir -p $(dir $@)
	$(Q)rgbgfx $< -o $@

$(BUILD)/assets/%.oam.2bpp: assets/%.oam.png
	@echo Converting $<
	@mkdir -p $(dir $@)
	$(Q)rgbgfx -h $< -o $@

$(BUILD)/assets/%.1bpp: assets/%.png
	@echo Converting $<
	@mkdir -p $(dir $@)
	$(Q)rgbgfx -d 1 $< -o $@

# Special hack to place a ret instruction at the end of the GSINIT section.
# This has to be linked last, as that ensures that this fragment is at the end of the "GSINIT" section.
$(BUILD)/gsinit.end.o:
	@printf 'SECTION FRAGMENT "GSINIT", ROMX, BANK[1]\n  ret' | rgbasm - -o $@

clean:
	@rm -rf $(BUILD) $(PROJECT_NAME).$(ROM_EXTENSION) $(PROJECT_NAME).map $(PROJECT_NAME).sym

# Do not remove intermediate files (like assets, c->asm files, etc)
.SECONDARY:
