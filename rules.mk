.PHONY: all clean

MYDIR     := $(dir $(lastword $(MAKEFILE_LIST)))

ifndef PROJECT_NAME
$(error PROJECT_NAME is not set)
endif
ifndef MBC
$(error MBC is not set.)
endif

SRC       := $(shell find src/ -type f -name '*.c') $(shell find $(MYDIR)/src/ -type f -name '*.c')
ASM       := $(shell find src/ -type f -name '*.asm') $(shell find $(MYDIR)/src/ -type f -name '*.asm')

# Which files do we use from the sdcc libc
LIBC    := _memset.c gbz80/memcpy.s
LIBC_PATH := $(shell sdcc -mgbz80 --print-search-dirs | grep gbz80 | tail -n 1)/../src
LIBC_PATH := /usr/local/share/sdcc/lib/src

Q ?= @

BUILD    := _build
TOOLS    := $(MYDIR)/tools
OBJS     := $(patsubst %, $(BUILD)/%.o, $(ASM) $(SRC)) $(patsubst %, $(BUILD)/libc/%.o, $(LIBC)) $(BUILD)/gsinit.end.o

CFLAGS   := -mgbz80 -Isrc/ -I$(MYDIR)/inc
ASFLAGS  := -isrc/ -i$(MYDIR)/inc -i$(BUILD)/assets/ -Wall
LDFLAGS  := -p 0xFF --dmg
FIXFLAGS := -v -p 0xFF -t $(NAME) -m $(MBC)


all: $(PROJECT_NAME).gb

$(BUILD)/%.c.as: %.c Makefile
	@echo Compiling $<
	@mkdir -p $(dir $@)
	$(Q)sdcc $(CFLAGS) -S $< -o $@ -Wp "-MQ $@ -MD $(@:.as=.d)"
-include $(patsubst %.c, $(BUILD)/%.c.d, $(SRC))

$(BUILD)/libc/%.c.as: $(LIBC_PATH)/%.c
	@echo Compiling $<
	@mkdir -p $(dir $@)
	$(Q)sdcc $(CFLAGS) -S $< -o $@

$(BUILD)/%.c.asm: $(BUILD)/%.c.as $(TOOLS)/asmconvert.py
	$(Q)python3 $(TOOLS)/asmconvert.py $(notdir $<) < $< > $@

$(BUILD)/libc/%.s.asm: $(LIBC_PATH)/%.s $(TOOLS)/asmconvert.py
	@mkdir -p $(dir $@)
	$(Q)python3 $(TOOLS)/asmconvert.py $(notdir $<) < $< > $@

$(BUILD)/%.d: $(BUILD)/%.asm
	@mkdir -p $(dir $@)
	$(Q)rgbasm $(ASFLAGS) $< -M $@ -MT $(@:.d=.o) -MT $@ -MG
-include $(patsubst %.asm, $(BUILD)/%.asm.d, $(ASM))

$(BUILD)/%.o: $(BUILD)/%.asm $(BUILD)/%.d
	@echo Assembling $<
	@mkdir -p $(dir $@)
	$(Q)rgbasm $(ASFLAGS) $< -o $@

$(BUILD)/%.asm.d: %.asm
	@mkdir -p $(dir $@)
	$(Q)rgbasm $(ASFLAGS) $< -M $@ -MT $(@:.d=.o) -MT $@ -MG
-include $(patsubst %.asm, $(BUILD)/%.asm.d, $(ASM))

$(BUILD)/%.asm.o: %.asm $(BUILD)/%.asm.d
	@echo Assembling $<
	@mkdir -p $(dir $@)
	$(Q)rgbasm $(ASFLAGS) $< -o $@

$(PROJECT_NAME).gb: $(OBJS)
	@echo Linking $@
	$(Q)rgblink $(LDFLAGS) $^ -o $@ -m $(basename $@).map -n $(basename $@).sym
	$(Q)rgbfix $(FIXFLAGS) $@
	@python3 $(TOOLS)/romspace.py $(basename $@).map

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

$(BUILD)/gsinit.end.asm:
    # Special hack to place a ret instruction at the end of the GSINIT section.
	@echo 'SECTION FRAGMENT "GSINIT", ROMX, BANK[1]\n  ret' > $@

clean:
	@rm -rf $(BUILD) $(PROJECT_NAME).gb

# Do not remove intermediate files (like assets, c->asm files, etc)
.SECONDARY:
