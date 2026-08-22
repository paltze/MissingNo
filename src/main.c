#include <stdio.h>
#include <stdlib.h>

#include "commons.h"
#include "startup.h"
#include "init.h"

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        perror("Pass file path to ROM\n");
        return EXIT_FAILURE;
    }

    Emu* emu = NULL;
    if (!init_new_emu(&emu)) {
        perror("Couldn't allocate memory for emulator\n");
        return EXIT_FAILURE;
    }

    u8* ROM = emu->ROM;
    if (!init_read_ROM(emu->ROM, argv[1])) {
        perror("Couldn't read ROM\n");
        return EXIT_FAILURE;
    }

    if (!startup_graphics_check(ROM)) {
        printf("Nintendo Graphic mismatch: terminating\n");
        free(emu);
        return EXIT_FAILURE;
    }

    printf("Nintendo Graphic OK\n");

    if (!startup_header_checksum(ROM)) {
        printf("Header Checksum mismatch: terminating\n");
        free(emu);
        return EXIT_FAILURE;
    }

    printf("Header Checksum matched\n");

    if (!startup_global_checksum(ROM))
        printf("Global Checksum mismatch\n");
    else
        printf("Global Checksum matched\n");

    char title[16];
    startup_game_title(ROM, title);

    printf("Game Title: %s\n", title);
    printf("ROM Type: %s\n", startup_ROM_type_name(startup_ROM_type(ROM)));
    printf("Cartridge Type: %s\n", startup_cartridge_type_name(startup_cartridge_type(ROM)));
    printf("ROM Size: %zu bytes\n", startup_ROM_size(ROM));
    printf("RAM Size: %zu bytes\n", startup_RAM_size(ROM));

    free(emu);

    return 0;
}
