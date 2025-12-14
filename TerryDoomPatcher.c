#define _CRT_SECURE_NO_WARNINGS //obejscie bledu fopen unsafe
#include <stdio.h>
#include <stdint.h> //int types
#include "wad.h"

int main()
{
    printf("hello world!\n");

    wadHeader naglowek;

    FILE* doomFile = fopen("DOOM1.WAD", "rb");
    if (doomFile) {
        printf("wczytano plik DOOMa\n");
        fread(&naglowek, 4, 3, doomFile);
        printf("typ pliku: %s\n", naglowek.wadType);
        printf("ilosc lumps: %d\n", naglowek.numLumps);
    }
    else {
        printf("error, nie udalo sie uzyskac dostepu do pliku");
        fclose(doomFile);
    }

    return 0;
}
