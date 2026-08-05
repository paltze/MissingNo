#include <stdio.h>

#define u8 unsigned char

int main() {
    u8 memory[65536];

    FILE* ROM = fopen("./PokemonRed.gb", "rb");
    FILE* fp = fopen("./out.txt", "w");

    u8 byte;
    size_t i = 0;

    while (fread(&byte, 1, 1, ROM) == 1) {
        fprintf(fp, "%02X\n", byte);

        if (i >= 0x0134 && i <= 0x0142)
            printf("%c", byte);

        i++;
    }

    printf("\n");

    fclose(ROM);
    fclose(fp);

    return 0;
}
