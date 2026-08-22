#include "init.h"

#include <stdio.h>
#include <stdlib.h>

bool init_new_emu(Emu** emu) {
    *emu = calloc(1, sizeof(Emu));

    if (*emu == NULL)
        return false;

    return true;
}

bool init_read_ROM(u8* ROM, char* path) {
    FILE* ROM_file = fopen(path, "rb");

    if (ROM_file == NULL) {
        fclose(ROM_file);
        return false;
    }

    fread(ROM, sizeof(u8), 2 * 1024 * 1024, ROM_file);

    if (ferror(ROM_file)) {
        fclose(ROM_file);
        return false;
    }

    fclose(ROM_file);
    return true;
}


