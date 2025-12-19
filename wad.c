#include <stdio.h>
#include <stdlib.h> //malloc
#include "wad.h"

lumpInfo* new_lump() {
    lumpInfo* result = malloc(sizeof(lumpInfo));
    result->next = NULL;
    return result;
}

void print_lumps(lumpInfo* head) {
    lumpInfo* tmp = head;

    while (tmp != NULL) {
        printf("nazwa zasobu: %.8s\n", tmp->lumpName);
        printf("wielkosc zasobu w bajtach: %d\n", tmp->lumpSizeBytes);
        tmp = tmp->next;
    }
}