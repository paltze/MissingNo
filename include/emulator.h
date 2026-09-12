#ifndef EMULATOR_H
#define EMULATOR_H

#include "commons.h"
#include "startup.h"

typedef enum {
    A, F,
    B, C,
    D, E,
    H, L
} Regs;

typedef struct {
    u8 ROM[0x200000];
    u8 r[8];
    u16 SP;
    u16 PC;

    u8 internal_mem[0x2000];
    u8 sec_internal_mem[0x7F];
    u8 cart_mem[0x20000];
    u8 VRAM[0x2000];
    u8 IO[0x7F];
    u8 SAB[0xA0];
    u8 interr_en;

    MBC_Type mbc_type;
    
    u16 ROM_bank;
    u16 RAM_bank;
} Emu;

#endif
