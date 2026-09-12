#ifndef INIT_H
#define INIT_H

#include "commons.h"
#include "emulator.h"

bool init_new_emu(Emu** emu);
bool init_read_ROM(u8* ROM, char* path);

#endif
