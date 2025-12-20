#define _CRT_SECURE_NO_WARNINGS //strcpy unsafe
#include <stdio.h>
#include <stdlib.h> //malloc
#include "wad.h"
#include <string.h>
#include <ctype.h>

lumpInfo* new_lump() {
    lumpInfo* result = malloc(sizeof(lumpInfo));
    result->next = NULL;
    return result;
}

void print_lumps(lumpInfo* head) {
    system("cls");
    lumpInfo* tmp = head;
    int c;

    while (tmp != NULL) {
        printf("%d - %.8s\n", tmp->lumpIndex, tmp->lumpName);
        printf("rozmiar zasobu w bajtach: %d\n", tmp->lumpSizeBytes);
        printf("pointer do danych: 0x%X\n", tmp->lumpPtr);
        tmp = tmp->next;
    }
    printf("\n\nwcisnij enter aby wrocic do menu");
    while (c = getchar() != '\n' && c != EOF);
    getchar();
    system("cls");
}

void switch_lumps(lumpInfo* first, lumpInfo* second) {
    lumpInfo tmp;
    tmp.lumpIndex = first->lumpIndex;
    strcpy(tmp.lumpName, first->lumpName);
    tmp.lumpPtr = first->lumpPtr;
    tmp.lumpSizeBytes = first->lumpSizeBytes;

    first->lumpIndex = second->lumpIndex;
    strcpy(first->lumpName, second->lumpName);
    first->lumpPtr = second->lumpPtr;
    first->lumpSizeBytes = second->lumpSizeBytes;

    second->lumpIndex = tmp.lumpIndex;
    strcpy(second->lumpName, tmp.lumpName);
    second->lumpPtr = tmp.lumpPtr;
    second->lumpSizeBytes = tmp.lumpSizeBytes;
}

void sort_lumps(lumpInfo* head) {
    int changed;
    int strcompare;
    int sortType;
    lumpInfo* tmp_tail = NULL;

    system("cls");
    printf("sortowanie po:\n");
    printf("1. rozmiarze zasobu\n");
    printf("2. alfabetycznie\n");
    printf("3. indeksie\n");
    while ((getchar()) != '\n');
    scanf("%d", &sortType);

    if (sortType == 1) {
        do {
            lumpInfo* tmp = head;
            changed = 0;
            while (tmp->next != tmp_tail) {
                if (tmp->lumpSizeBytes < tmp->next->lumpSizeBytes) {
                    switch_lumps(tmp, tmp->next);
                    changed = 1;
                }
                tmp = tmp->next;
            }
        } while (changed);
    }
    if (sortType == 2) {
        do {
            lumpInfo* tmp = head;
            changed = 0;
            while (tmp->next != tmp_tail) {
                strcompare = strcmp(tmp->lumpName, tmp->next->lumpName);
                if (strcompare > 0) {
                    switch_lumps(tmp, tmp->next);
                    changed = 1;
                }
                tmp = tmp->next;
            }
        } while (changed);
    }
    if (sortType == 3) {
        do {
            lumpInfo* tmp = head;
            changed = 0;
            while (tmp->next != tmp_tail) {
                if (tmp->lumpIndex < tmp->next->lumpIndex) {
                    switch_lumps(tmp, tmp->next);
                    changed = 1;
                }
                tmp = tmp->next;
            }
        } while (changed);
    }
}

void string_to_upper(char* text) {
    for (int i = 0; i < strlen(text); i++) {
        text[i] = toupper(text[i]);
    }
}

void find_lumps(lumpInfo* head, char phrase[128]) {
    lumpInfo* tmp = head;
    int licznik = 0;
    char tempName[9];
    string_to_upper(phrase);
    strncpy(tempName, tmp->lumpName, 8);
    tempName[8] = '\0';

    while (tmp != NULL) {
        strncpy(tempName, tmp->lumpName, 8);
        tempName[8] = '\0';
        char* wynik = strstr(tempName, phrase);
        if (wynik != NULL) {
            printf("%s\n", tempName);
            licznik++;
        }
        tmp = tmp->next;
    }
    printf("\nliczba wystapien frazy \"%s\" : %d", phrase, licznik);
    printf("\n\nwcisnij enter aby wrocic do menu");
    while (getchar() != '\n');
    getchar();
    system("cls");
}

void export_lump(FILE* filename, lumpInfo* head) {
    system("cls");
    lumpInfo* tmp = head;
    char phrase[128];
    char destFileName[128];
    int found = 0;
    printf("podaj dokladna nazwe zasobu:");
    scanf("%s", phrase);
    string_to_upper(phrase);
    while (tmp != NULL) {
        char safeName[9];
        strncpy(safeName, tmp->lumpName, 8);
        safeName[8] = '\0';
        if (strcmp(safeName, phrase) == 0) {
            printf("mamy match: %s, size: %d\n", tmp->lumpName, tmp->lumpSizeBytes);
            found = 1;
            printf("podaj nazwe pliku wyjsciowego: ");
            scanf("%s", destFileName);
            fseek(filename, tmp->lumpPtr, SEEK_SET);
            unsigned char *buffor = malloc(tmp->lumpSizeBytes);
            fread(buffor, tmp->lumpSizeBytes, 1, filename);
            FILE* destFile = fopen(destFileName, "wb");
            fwrite(buffor, tmp->lumpSizeBytes, 1, destFile);
            fclose(destFile);
            free(buffor);
        }
        tmp = tmp->next;
    }
    if (found == 0) {
        printf("nie znaleziono podanej frazy\n");
    }
    printf("\n\nwcisnij enter aby wrocic do menu");
    while (getchar() != '\n');
    getchar();
    system("cls");
}