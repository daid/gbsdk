import sys
import re

SIZE = {"ROM0": 0x4000, "ROMX": 0x4000, "WRAM0": 0x2000, "SRAM": 0x2000, "HRAM": 0x007F, "VRAM": 0x4000}

area_re = re.compile(r'([A-Z0-9]+) bank #([0-9a-f]+):\n')
slack_re = re.compile(r'    SLACK: \$([0-9a-f]+) byte')
areas = []
for line in open(sys.argv[1], "rt"):
    area = area_re.match(line)
    if area:
        area_name = area[1]
        bank_nr = int(area[2])
    slack = slack_re.match(line)
    if slack:
        areas.append((area_name, bank_nr, int(slack[1], 16)))

# Change size of ROM0 to 8000 if there are no ROMX sections.
# Needed when using the '--tiny' option with RGBLINK.
if not any([x for x in areas if x[0] == "ROMX"]):
    SIZE["ROM0"] = 0x8000

for area in areas:
    used = SIZE[area[0]] - area[2]
    print("%5s:%2d %04x/%04x (%.1f%%)" % (area[0], area[1], used, SIZE[area[0]], used * 100 / SIZE[area[0]]))
