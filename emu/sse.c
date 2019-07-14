#include <math.h>

#include "emu/cpu.h"

void vec_compare32(struct cpu_state *cpu, float *f2, float *f1) {
    if (isnan(*f1) || isnan(*f2)) {
        cpu->zf = 1;
        cpu->pf = 1;
        cpu->cf = 1;
    }
    else if (*f1 > *f2) {
        cpu->zf = 0;
        cpu->pf = 0;
        cpu->cf = 0;
    }
    else if (*f1 < *f2) {
        cpu->zf = 0;
        cpu->pf = 0;
        cpu->cf = 1;
    }
    else if (*f1 == *f2) {
        cpu->zf = 1;
        cpu->pf = 0;
        cpu->cf = 0;
    }
    else {
        printf("something's horribly wrong. err 1093281094");
    }
    cpu->zf_res = 0;
    cpu->pf_res = 0;
}

void vec_load32(struct cpu_state *UNUSED(cpu), union xmm_reg *src, union xmm_reg *dst) {
    *((float*)&dst->dw[0]) = *((float*)&src->dw[0]);
}
void vec_load64(struct cpu_state *UNUSED(cpu), union xmm_reg *src, union xmm_reg *dst) {
    dst->qw[0] = src->qw[0];
}
void vec_load128(struct cpu_state *UNUSED(cpu), union xmm_reg *src, union xmm_reg *dst) {
            *((float*)&src->dw[0]),
            *((float*)&src->dw[1]),
            *((float*)&src->dw[2]),
            *((float*)&src->dw[3]),
            *((float*)&dst->dw[0]),
            *((float*)&dst->dw[1]),
            *((float*)&dst->dw[2]),
            *((float*)&dst->dw[3])
            );
    *dst = *src;
}

static inline void zero_xmm(union xmm_reg *xmm) {
    xmm->qw[0] = 0;
    xmm->qw[1] = 0;
}
#define ZLOAD(sz) \
void vec_zload##sz(struct cpu_state *cpu, union xmm_reg *src, union xmm_reg *dst) { \
    zero_xmm(dst); \
    vec_load##sz(cpu, src, dst); \
}
ZLOAD(32)
ZLOAD(64)
ZLOAD(128)
#undef ZLOAD

void vec_store32(struct cpu_state *UNUSED(cpu), union xmm_reg *dst, union xmm_reg *src) {
    dst->dw[0] = src->dw[0];
}
void vec_store64(struct cpu_state *UNUSED(cpu), union xmm_reg *dst, union xmm_reg *src) {
    dst->qw[0] = src->qw[0];
}
void vec_store128(struct cpu_state *UNUSED(cpu), union xmm_reg *dst, union xmm_reg *src) {
    *dst = *src;
}

void vec_xor128(struct cpu_state *UNUSED(cpu), union xmm_reg *src, union xmm_reg *dst) {
    dst->qw[0] ^= src->qw[0];
    dst->qw[1] ^= src->qw[1];
}

