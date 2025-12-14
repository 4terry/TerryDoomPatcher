#pragma once

#include <stdint.h>

typedef struct {
    char wadType[4];    // 0x00
    int32_t numLumps;   // 0x04
    int32_t dirPtr;     // 0x08
} wadHeader;