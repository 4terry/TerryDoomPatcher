#define _CRT_SECURE_NO_WARNINGS //obejscie bledu fopen unsafe
#include <stdio.h>
#include <stdint.h> //int types
#include <stdlib.h> //malloc
#include <string.h>
#include "wad.h"

void logo();

int main()
{
    char doomFileName[32];
    char phrase[128];

    while (1) {
        logo();
        printf("podaj nazwe pliku WAD umieszczonego w folderze z programem:\n");
        scanf("%s", doomFileName);

        wadHeader naglowek;

        FILE* doomFile = fopen(doomFileName, "rb");
        if (doomFile) {
            system("cls");
            logo();
            fread(&naglowek, 4, 3, doomFile);
            int wybor;
            lumpInfo* head = NULL;
            lumpInfo* tail = NULL;
            lumpInfo* tmp = NULL;
            fseek(doomFile, naglowek.dirPtr, SEEK_SET);

            for (int i = 0; i < naglowek.numLumps; i++) {
                tmp = new_lump();
                fread(tmp, 16, 1, doomFile);
                tmp->next = NULL;
                if (head == NULL) {
                    head = tmp;
                    tail = tmp;
                }
                else {
                    tail->next = tmp;
                    tail = tmp;
                }
                tmp->index = i+1;
            }
            while (doomFile) {
                system("cls");
                logo();
                printf("wczytano plik DOOMa: %s\n", doomFileName);
                printf("typ pliku: %.4s\n", naglowek.wadType);
                printf("ilosc zasobow: %d (w bajtach: %d)\n", naglowek.numLumps, naglowek.numLumps * 16);
                printf("pointer do tabeli zasobow: 0x%X\n\n", naglowek.dirPtr);

                printf("1. wyswietl wszystko\n");
                printf("2. exportuj zasob\n");
                printf("3. widok posortowany\n");
                printf("4. szukaj zasobu\n");
                printf("5. wyjscie\n");
                if (scanf("%d", &wybor) != 1) {
                    while ((getchar()) != '\n');
                }

                switch (wybor) {
                case 1:
                    system("cls");
                    print_lumps(head);
                    break;
                case 2:
                    system("cls");
                    char destname[128];
                    export_lump(doomFile, head, destname);
                    break;
                case 3:
                    system("cls");
                    printf("sortowanie po:\n");
                    printf("1. rozmiarze\n");
                    printf("2. alfabetycznie\n");
                    while ((getchar()) != '\n');
                    scanf("%d", &wybor);
                    switch (wybor) {
                    case 1:
                        system("cls");
                        sort_lumps(head, 1);
                        print_lumps(head);
                        break;
                    case 2:
                        system("cls");
                        sort_lumps(head, 2);
                        print_lumps(head);
                        break;
                    default:
                        break;
                    }
                case 4:
                    system("cls");
                    printf("podaj wyszukiwana fraze: ");
                    scanf("%s", phrase);
                    printf("\n");
                    find_lumps(head, phrase);
                    break;
                case 5:
                    return 0;
                    break;
                default:
                    break;
                }
            }
        }
        else {
            system("cls");
            printf("error, nie udalo sie uzyskac dostepu do pliku\n");
        }
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