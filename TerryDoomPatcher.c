#define _CRT_SECURE_NO_WARNINGS //obejscie bledu fopen unsafe
#include <stdio.h>
#include <stdint.h> //int types
#include <stdlib.h> //malloc
#include <string.h>
#include "wad.h"

void logo();
lumpInfo* new_lump();

int main()
{
    logo();
    wadHeader naglowek;

    FILE* doomFile = fopen("DOOM1.WAD", "rb");
    if (doomFile) {
        printf("wczytano plik DOOMa\n");
        fread(&naglowek, 4, 3, doomFile);
        printf("typ pliku: %.4s\n", naglowek.wadType);
        printf("ilosc zasobow: %d (w bajtach: %d)\n", naglowek.numLumps, naglowek.numLumps*16);
        printf("pointer do zasobow: 0x%X\n", naglowek.dirPtr);

        lumpInfo* head = NULL;
        lumpInfo* tmp = NULL;
        fseek(doomFile, naglowek.dirPtr, SEEK_SET);

        for (int i = 1; i < naglowek.numLumps; i++) {
            tmp = new_lump();
            fread(tmp, 16, 1, doomFile);
            tmp->next = head;
            head = tmp;
            printf("nazwa zasobu: %.8s\n", head->lumpName);
            printf("wielkosc zasobu w bajtach: %d\n", head->lumpSizeBytes);
        }

    }
    else {
        printf("error, nie udalo sie uzyskac dostepu do pliku");
        fclose(doomFile);
    }

    return 0;
}

void logo() {
    printf("\n");
    printf("___________                         ________                       __________         __         .__                  \n");
    printf("\\__    ___/_________________ ___.__.\\______ \\   ____   ____   _____\\______   \\_____ _/  |_  ____ |  |__   ___________ \n");
    printf("  |    |_/ __ \\_  __ \\_  __ <   |  | |    |  \\ /  _ \\ /  _ \\ /     \\|     ___/\\__  \\\\   __\\/ ___\\|  |  \\_/ __ \\_  __ \\\n");
    printf("  |    |\\  ___/|  | \\/|  | \\/\\___  | |    `   (  <_> |  <_> )  Y Y  \\    |     / __ \\|  | \\  \\___|   Y  \\  ___/|  | \\/\n");
    printf("  |____| \\___  >__|   |__|   / ____|/_______  /\\____/ \\____/|__|_|  /____|    (____  /__|  \\___  >___|  /\\___  >__|   \n");
    printf("             \\/              \\/             \\/                    \\/               \\/          \\/     \\/     \\/       \n");
}

lumpInfo* new_lump() {
    lumpInfo* result = malloc(sizeof(lumpInfo));
    result->next = NULL;
    return result;
}