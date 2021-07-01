import sys
import re

SIZE = {"ROM0": 0x4000, "ROMX": 0x4000, "WRAM0": 0x2000, "HRAM": 0x007F, "VRAM": 0x4000}

area_re = re.compile(r'([A-Z0-9]+) bank #([0-9a-f]+):\n')
slack_re = re.compile(r'    SLACK: \$([0-9a-f]+) byte')
for line in open(sys.argv[1], "rt"):
    area = area_re.match(line)
    if area:
        area_name = area[1]
        bank_nr = int(area[2])
    slack = slack_re.match(line)
    if slack:
        used = SIZE[area_name] - int(slack[1], 16)
        print("%5s:%2d %04x/%04x (%.1f%%)" % (area_name, bank_nr, used, SIZE[area_name], used * 100 / SIZE[area_name]))
