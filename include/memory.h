#ifndef MEMORY_H
#define MEMORY_H

#include "commons.h"
#include "emulator.h"

u8 read_memory(Emu* emu, u16 loc);
void write_memory(Emu* emu, u16 loc, u8 val);

#endif
