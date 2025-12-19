#pragma once

#include <stdint.h>

typedef struct {
    char wadType[4];    // 0x00
    int32_t numLumps;   // 0x04
    int32_t dirPtr;     // 0x08
} wadHeader;

typedef struct lumpInfo {
    int32_t lumpPtr;
    int32_t lumpSizeBytes;
    char lumpName[8];
    int index;
    struct lumpInfo* next;
} lumpInfo;

lumpInfo* new_lump();
void print_lumps(lumpInfo* head);
void switch_lumps(lumpInfo* first, lumpInfo* second);
void sort_lumps(lumpInfo* head, int sort_type);