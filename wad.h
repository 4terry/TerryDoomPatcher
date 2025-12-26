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
    int lumpIndex;
    struct lumpInfo* next;
} lumpInfo;

lumpInfo* new_lump();
void print_lumps(lumpInfo* head);
void switch_lumps(lumpInfo* first, lumpInfo* second);
void sort_lumps(lumpInfo* head);
void string_to_upper(char* text);
void find_lumps(lumpInfo* head, char phrase[128]);
void export_lump(FILE* wadFile, lumpInfo* head);
void import_lump(FILE* wadFile, lumpInfo* head, int32_t lumpsDir);