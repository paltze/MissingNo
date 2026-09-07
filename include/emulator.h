#ifndef EMULATOR_H
#define EMULATOR_H

#include "commons.h"

u8 read_memory(Emu* emu, u16 loc);
void write_memory(Emu* emu, u16 loc, u8 val);

#endif
