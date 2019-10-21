#ifndef CPUID_H
#define CPUID_H

#include "misc.h"

static int SSE2 = 1 << 26;
static int CMOV = 1 << 15;

static inline void do_cpuid(dword_t *eax, dword_t *ebx, dword_t *ecx, dword_t *edx) {
    dword_t leaf = *eax;
    switch (leaf) {
        case 0:
            *eax = 0x01; // we support barely anything
            *ebx = 0x756e6547; // Genu
            *edx = 0x49656e69; // ineI
            *ecx = 0x6c65746e; // ntel
            break;
        default: // if leaf is too high, use highest supported leaf
        case 1:
            *eax = 0x0; // say nothing about cpu model number
            *ebx = 0x0; // processor number 0, flushes 0 bytes on clflush
            *ecx = 0b00000000000000000000000000000000; // we support none of the features in ecx
            *edx = CMOV /* | SSE2 */; // Enable when SSE2 is in a more stable state
            break;
    }
}

#endif
