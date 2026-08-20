#include <stdio.h>
#include <stdlib.h>

#include "commons.h"
#include "startup.h"

int main(void) {
    FILE* ROM_file = fopen("./ROMS/PokemonRed.gb", "rb");

    if (ROM_file == NULL) {
        perror("Failed to open ROM");
        return EXIT_FAILURE;
    }

    u8* ROM = calloc(2 * 1024 * 1024, sizeof(u8));

    if (ROM == NULL) {
        perror("Failed to allocate ROM memory");
        fclose(ROM_file);
        return EXIT_FAILURE;
    }

    fread(ROM, sizeof(u8), 2 * 1024 * 1024, ROM_file);

    if (ferror(ROM_file)) {
        perror("Failed to read ROM");
        free(ROM);
        fclose(ROM_file);
        return EXIT_FAILURE;
    }

    fclose(ROM_file);

    if (!startup_graphics_check(ROM)) {
        printf("Nintendo Graphic mismatch: terminating\n");
        free(ROM);
        return EXIT_FAILURE;
    }

    printf("Nintendo Graphic OK\n");

    if (!startup_header_checksum(ROM)) {
        printf("Header Checksum mismatch: terminating\n");
        free(ROM);
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

    free(ROM);

    return 0;
}
