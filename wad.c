#define _CRT_SECURE_NO_WARNINGS //strcpy unsafe
#include <stdio.h>
#include <stdlib.h> //malloc
#include "wad.h"
#include <string.h>

lumpInfo* new_lump() {
    lumpInfo* result = malloc(sizeof(lumpInfo));
    result->next = NULL;
    return result;
}

void print_lumps(lumpInfo* head) {
    lumpInfo* tmp = head;

    while (tmp != NULL) {
        printf("%d - %.8s\n", tmp->index, tmp->lumpName);
        printf("wielkosc zasobu w bajtach: %d\n", tmp->lumpSizeBytes);
        tmp = tmp->next;
    }
    printf("\n\nwcisnij enter aby wrocic do menu");
    while (getchar() != '\n');
    getchar();
    system("cls");
}

void switch_lumps(lumpInfo* first, lumpInfo* second) {
    lumpInfo tmp;
    tmp.index = first->index;
    strcpy(tmp.lumpName, first->lumpName);
    tmp.lumpPtr = first->lumpPtr;
    tmp.lumpSizeBytes = first->lumpSizeBytes;

    first->index = second->index;
    strcpy(first->lumpName, second->lumpName);
    first->lumpPtr = second->lumpPtr;
    first->lumpSizeBytes = second->lumpSizeBytes;

    second->index = tmp.index;
    strcpy(second->lumpName, tmp.lumpName);
    second->lumpPtr = tmp.lumpPtr;
    second->lumpSizeBytes = tmp.lumpSizeBytes;
}

void sort_lumps(lumpInfo* head, int sort_type) {
    int changed;
    lumpInfo* tmp_tail = NULL;
    if (sort_type == 1) {
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
}