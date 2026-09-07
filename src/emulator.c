#include "emulator.h"

u8 read_memory(Emu* emu, u16 loc) {
    if (loc < 0x4000)
        return emu->ROM[loc];
    
}

void write_memory(Emu* emu, u16 loc, u8 val) {

}