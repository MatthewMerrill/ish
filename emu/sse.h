#ifndef EMU_SSE_H
#define EMU_SSE_H

#include "emu/cpu.h"

void vec_compare32(struct cpu_state *UNUSED(cpu), float *f2, float *f1);

/**
 * If either arg is memory, the mem arg must be in the first position.
 *
 * Convention:
 * =============================
 * - If and only if the helper must write to memory, use v_write(...).
 * - Make args const unless absolutely necessary.
 * 
 *  writes to mem | jit/gen method | arg order
 * ---------------|----------------|------------
 *  No            | v()            | const a, b    
 *  Yes           | v_write()      | a, const b
 */

void vec_compare_each8(struct cpu_state *UNUSED(cpu), const union xmm_reg *cmp, union xmm_reg *dst);
void vec_compare_each32(struct cpu_state *UNUSED(cpu), const union xmm_reg *cmp, union xmm_reg *dst);
void vec_movmsk8(struct cpu_state *UNUSED(cpu), uint32_t *dst, const union xmm_reg *src);

void vec_load32(struct cpu_state *UNUSED(cpu), const union xmm_reg *src, union xmm_reg *dst);
void vec_load64(struct cpu_state *UNUSED(cpu), const union xmm_reg *src, union xmm_reg *dst);
void vec_load128(struct cpu_state *UNUSED(cpu), const union xmm_reg *src, union xmm_reg *dst);

// Zeroes out the destination before loading.
// Used in some instructions like movss when the src is memory.
void vec_zload32(struct cpu_state *UNUSED(cpu), const union xmm_reg *src, union xmm_reg *dst);
void vec_zload64(struct cpu_state *UNUSED(cpu), const union xmm_reg *src, union xmm_reg *dst);
void vec_zload128(struct cpu_state *UNUSED(cpu), const union xmm_reg *src, union xmm_reg *dst);

void vec_store32(struct cpu_state *UNUSED(cpu), union xmm_reg *dst, const union xmm_reg *src);
void vec_store64(struct cpu_state *UNUSED(cpu), union xmm_reg *dst, const union xmm_reg *src);
void vec_store128(struct cpu_state *UNUSED(cpu), union xmm_reg *dst, const union xmm_reg *src);

// Zeroes out the destination before storing.
// Used in some instructions like movq when the dst is register.
void vec_zstore32(struct cpu_state *UNUSED(cpu), union xmm_reg *dst, const union xmm_reg *src);
void vec_zstore64(struct cpu_state *UNUSED(cpu), union xmm_reg *dst, const union xmm_reg *src);
void vec_zstore128(struct cpu_state *UNUSED(cpu), union xmm_reg *dst, const union xmm_reg *src);

void vec_imm_shiftl64(struct cpu_state *UNUSED(cpu), const uint8_t amount, union xmm_reg *src);
void vec_imm_shiftr64(struct cpu_state *UNUSED(cpu), const uint8_t amount, union xmm_reg *src);

void vec_shiftr64(struct cpu_state *UNUSED(cpu), const union xmm_reg *arg, union xmm_reg *dst);

void vec_add64(struct cpu_state *UNUSED(cpu), const union xmm_reg *arg, union xmm_reg *dst);
void vec_muls64(struct cpu_state *UNUSED(cpu), const union xmm_reg *arg, union xmm_reg *dst);

void vec_and128(struct cpu_state *cpu, const union xmm_reg *arg, union xmm_reg *dst);
void vec_or128(struct cpu_state *cpu, const union xmm_reg *arg, union xmm_reg *dst);
void vec_xor128(struct cpu_state *cpu, union xmm_reg *src, union xmm_reg *dst);

#endif
