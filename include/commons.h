#ifndef COMMONS_H
#define COMMONS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define u8 uint8_t
#define u16 uint16_t

typedef enum {
    A, F,
    B, C,
    D, E,
    H, L
} Regs;

typedef struct {
    u8 ROM[0x200000];
    u8 mem[0x2000];
    u8 r[8];
    u16 SP;
    u16 PC;
} Emu;

#endif
