#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define u8 uint8_t
#define u16 uint16_t

void fixed_checks(u8* ROM) {
    // Nintendo Graphic check
    u8 sig[] = {
        0xCE,
        0xED,
        0x66,
        0x66,
        0xCC,
        0x0D,
        0x00,
        0x0B,
        0x03,
        0x73,
        0x00,
        0x83,
        0x00,
        0x0C,
        0x00,
        0x0D,
        0x00,
        0x08,
        0x11,
        0x1F,
        0x88, 
        0x89,
        0x00,
        0x0E,
        0xDC,
        0xCC,
        0x6E,
        0xE6,
        0xDD,
        0xDD,
        0xD9,
        0x99,
        0xBB,
        0xBB,
        0x67,
        0x63,
        0x6E,
        0x0E,
        0xEC,
        0xCC,
        0xDD,
        0xDC,
        0x99,
        0x9F,
        0xBB,
        0xB9,
        0x33,
        0x3E
    };

    int ok = 1;

    for (int i = 0x104; i <= 0x133; i++) {
        if (ROM[i] != sig[i - 0x104]) {
            ok = 0;
        }
    }

    if (ok) {
        printf("Nintendo Graphic OK\n");
    }
    else {
        printf("Nintendo Graphic mismatch: terminating\n");
        return;
    }

    // Header Checksum check:
    u8 x = 0;
    for (int i = 0x0134; i <= 0x014C; i++)
        x = x - ROM[i] - 1;

    if (x == ROM[0x14D]) {
        printf("Header Checksum matched\n");
    }
    else {
        printf("Error: Header Checksum mismatch: terminating\n");
        return;
    }

    // Globabl Checksum Check:
    u16 sum = 0;

    for (int i = 0; i <= 0x14D; i++) {
        sum += ROM[i];
    }
    for (int i = 0x150; i <= 2 * 1024 * 1024; i++) {
        sum += ROM[i];
    }

    u16 tmp = ROM[0x14E];
    tmp <<= 8;
    tmp += ROM[0x14F];

    if (sum == tmp) {
        printf("Global Checksum matched\n");
    }
    else {
        printf("Global Checksum mismatch\n");
    }

    // Game Title
    printf("Game Title: ");
    for (int i = 0x134; i <= 0x142; i++) {
        printf("%c", ROM[i]);
    }
    printf("\n");

    // ROM Type
    printf("ROM Type: ");
    switch (ROM[0x143]) {
        case 0x80:
            printf("Dual mode Game Boy / Game Boy Color\n");
            break;
        case 0xC0:
            printf("Game Boy Color only\n");
            break;
        default:
            printf("Original Game Boy\n");
    }

    // Cartridge type
    printf("Cartridge Type: ");
    switch (ROM[0x147]) {
        case 0x0:
            printf("ROM only\n");
            break;
        case 0x1:
            printf("ROM+MBC1\n");
            break;
        case 0x2:
            printf("ROM+MBC1+RAM\n");
            break;
        case 0x3:
            printf("ROM+MBC1+RAM+BATT\n");
            break;
        case 0x5:
            printf("ROM+MBC2\n");
            break;
        case 0x6:
            printf("ROM+MBC2+BATTERY\n");
            break;
        case 0x8:
            printf("ROM+RAM\n");
            break;
        case 0x9:
            printf("ROM+RAM+BATTERY\n");
            break;
        case 0xB:
            printf("ROM+MMM01\n");
            break;
        case 0xC:
            printf("ROM+MMM01+SRAM\n");
            break;
        case 0xD:
            printf("ROM+MMM01+SRAM+BATT\n");
            break;
        case 0xF:
            printf("ROM+MBC3+TIMER+BATT\n");
            break;
        case 0x10:
            printf("ROM+MBC3+TIMER+RAM+BATT\n");
            break;
        case 0x11:
            printf("ROM+MBC3\n");
            break;
        case 0x12:
            printf("ROM+MBC3+RAM\n");
            break;
        case 0x13:
            printf("ROM+MBC3+RAM+BATT\n");
            break;
        case 0x19:
            printf("ROM+MBC5\n");
            break;
        case 0x1A:
            printf("ROM+MBC5+RAM\n");
            break;
        case 0x1B:
            printf("ROM+MBC5+RAM+BATT\n");
            break;
        case 0x1C:
            printf("ROM+MBC5+RUMBLE\n");
            break;
        case 0x1D:
            printf("ROM+MBC5+RUMBLE+SRAM\n");
            break;
        case 0x1E:
            printf("ROM+MBC5+RUMBLE+SRAM+BATT\n");
            break;
        case 0x1F:
            printf("Pocket Camera\n");
            break;
        case 0xFD:
            printf("Bundai TAMA5\n");
            break;
        case 0xFE:
            printf("Hudson HuC - 3\n");
            break;
        case 0xFF:
            printf("Hudson HuC - 1\n");
            break;
        default:
            printf("Error: unrecognised cartridge type: terminating\n");
            return;
    }

    // ROM Size
    printf("ROM Size: ");
    switch (ROM[0x148]) {
        case 0x0:
            printf("256K bit / 32K byte\n");
            break;
        case 0x1:
            printf("512K bit / 64K byte\n");
            break;
        case 0x2:
            printf("1M bit / 128K byte\n");
            break;
        case 0x3:
            printf("2M bit / 256K byte\n");
            break;
        case 0x4:
            printf("4M bit / 512K byte\n");
            break;
        case 0x5:
            printf("8M bit / 1M byte\n");
            break;
        case 0x6:
            printf("16M bit / 2M byte\n");
            break;
        case 0x52:
            printf("9M bit / 1.1M byte\n");
            break;
        case 0x53:
            printf("10M bit / 1.2M byte\n");
            break;
        case 0x54:
            printf("12M bit / 1.5M byte\n");
            break;
        default:
            printf("Error: unrecognised ROM size: terminating\n");
            return;
    }

    // RAM Size
    printf("RAM Size: ");
    switch (ROM[0x149]) {
        case 0:
            printf("None\n");
            break;
        case 1:
            printf("16K bit / 2K byte\n");
            break;
        case 2:
            printf("64K bit / 8K byte\n");
            break;
        case 3:
            printf("256K bit / 32K byte\n");
            break;
        case 4:
            printf("1M bit / 128K byte\n");
            break;
    }
}

int main() {
    u8* ROM = calloc(2 * 1024 * 1024, sizeof(u8));
    u8 memory[65536];

    FILE* ROM_file = fopen("./ROMS/PokemonRed.gb", "rb");

    u8 byte;
    size_t i = 0;

    while (fread(&byte, 1, 1, ROM_file) == 1) {
        ROM[i++] = byte;
    }

    fixed_checks(ROM);

    fclose(ROM_file);

    return 0;
}
