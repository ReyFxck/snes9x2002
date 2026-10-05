#ifndef _ASMMEMFUNCS_H_
#define _ASMMEMFUNCS_H_

#if defined(ARM_ASM)
#define memset32(_dst, _c, _count) \
({ uint32_t *dst = (_dst); uint32_t c __asm__ ("r7") = (_c); int count = (_count); uint32_t dummy0 __asm__ ("r4"), dummy1 __asm__ ("r5"), dummy2 __asm__ ("r6"); \
    __asm__ __volatile__ ( \
        "      cmp   %[count], #4\n" \
   "      blt   2f\n" \
        "      mov   %[dummy0], %[c]\n" \
   "      tst   %[dst], #4\n" \
   "      strne %[c], [%[dst]], #4\n" \
   "      subne %[count], %[count], #1\n" \
   "      tst   %[dst], #8\n" \
   "      stmneia %[dst]!, {%[dummy0], %[c]}\n" \
   "      subne %[count], %[count], #2\n" \
        "      mov   %[dummy1], %[c]\n" \
        "      mov   %[dummy2], %[c]\n" \
   "1:\n"\
   "      subs  %[count], %[count], #4\n" \
   "      stmgeia %[dst]!, {%[dummy0], %[dummy1], %[dummy2], %[c]}\n" \
   "      bge   1b\n" \
   "      add   %[count], %[count], #4\n" \
   "2:\n"\
   "      subs  %[count], %[count], #1\n" \
   "      strge %[c], [%[dst]], #4\n" \
   "      subs  %[count], %[count], #1\n" \
   "      strge %[c], [%[dst]], #4\n" \
   "      subs  %[count], %[count], #1\n" \
   "      strge %[c], [%[dst]], #4\n" \
   "\n" \
   : [dst] "+&r" (dst), [count] "+&r" (count), [dummy0] "=&r" (dummy0), [dummy1] "=&r" (dummy1), [dummy2] "=&r" (dummy2), [c] "+&r" (c) \
   : \
   : "cc", "memory" \
    ); _dst; \
})

#define memset16(_dst, _c, _count) \
({ uint16_t *dst = (_dst); uint16_t c __asm__ ("r7") = (_c); int count = (_count); uint32_t dummy0 __asm__ ("r4"), dummy1 __asm__ ("r5"), dummy2 __asm__ ("r6"); \
    __asm__ __volatile__ ( \
        "      cmp   %[count], #2\n" \
   "      blt   3f\n" \
   /* Alignment is known to be at least 16-bit */ \
        "      tst   %[dst], #2\n" \
   "      strneh %[c], [%[dst]], #2\n" \
   "      subne  %[count], %[count], #1\n" \
   /* Now we are 32-bit aligned (need to upgrade 'c' to 32-bit )*/ \
        "      orr    %[c], %[c], %[c], asl #16\n" \
        "      mov   %[dummy0], %[c]\n" \
        "      cmp   %[count], #8\n" \
   "      blt   2f\n" \
   "      tst   %[dst], #4\n" \
   "      strne %[c], [%[dst]], #4\n" \
   "      subne %[count], %[count], #2\n" \
   "      tst   %[dst], #8\n" \
   "      stmneia %[dst]!, {%[dummy0], %[c]}\n" \
   "      subne %[count], %[count], #4\n" \
   /* Now we are 128-bit aligned */ \
        "      mov   %[dummy1], %[c]\n" \
        "      mov   %[dummy2], %[c]\n" \
   "1:\n" /* Copy 4 32-bit values per loop iteration */ \
   "      subs  %[count], %[count], #8\n" \
   "      stmgeia %[dst]!, {%[dummy0], %[dummy1], %[dummy2], %[c]}\n" \
   "      bge   1b\n" \
   "      add   %[count], %[count], #8\n" \
   "2:\n" /* Copy up to 3 remaining 32-bit values */ \
   "      tst   %[count], #4\n" \
   "      stmneia %[dst]!, {%[dummy0], %[c]}\n" \
   "      tst   %[count], #2\n" \
   "      strne %[c], [%[dst]], #4\n" \
   "      and  %[count], %[count], #1\n" \
   "3:\n" /* Copy up to 1 remaining 16-bit value */ \
   "      subs  %[count], %[count], #1\n" \
   "      strgeh %[c], [%[dst]], #2\n" \
   "\n" \
   : [dst] "+&r" (dst), [count] "+&r" (count), [dummy0] "=&r" (dummy0), [dummy1] "=&r" (dummy1), [dummy2] "=&r" (dummy2), [c] "+&r" (c) \
   : \
   : "cc", "memory" \
    ); _dst;\
})

#define memcpy32(_dst, _src, _count) \
({ uint32_t *dst = (_dst); uint32_t *src = (_src); int count = (_count); \
    __asm__ __volatile__ ( \
        "      cmp   %[count], #4\n" \
   "      blt   2f\n" \
   "      tst   %[dst], #4\n" \
   "      ldrne r4, [%[src]], #4\n" \
   "      strne r4, [%[dst]], #4\n" \
   "      subne %[count], %[count], #1\n" \
   "      tst   %[dst], #8\n" \
   "      ldmneia %[src]!, {r4-r5}\n" \
   "      stmneia %[dst]!, {r4-r5}\n" \
   "      subne %[count], %[count], #2\n" \
   "1:\n" \
   "      subs  %[count], %[count], #4\n" \
   "      ldmgeia %[src]!, {r4-r7}\n" \
   "      stmgeia %[dst]!, {r4-r7}\n" \
   "      bge   1b\n" \
   "      add   %[count], %[count], #4\n" \
   "2:\n" \
   "      tst   %[count], #2\n" \
   "      ldmneia %[src]!, {r4-r5}\n" \
   "      stmneia %[dst]!, {r4-r5}\n" \
   "      tst   %[count], #1\n" \
   "      ldrne r4, [%[src]], #4\n" \
   "      strne r4, [%[dst]], #4\n" \
   "\n" \
   : [dst] "+&r" (dst),  [src] "+&r" (src), [count] "+&r" (count) \
   : \
   : "r4", "r5", "r6", "r7", "cc", "memory" \
    ); _dst; \
})

#define memcpy16(_dst, _src, _count) \
({ uint16_t *dst = (_dst); uint16_t *src = (_src); int count = (_count); uint32_t dummy0; \
    __asm__ __volatile__ ( \
        "      cmp   %[count], #2\n" \
   "      blt   6f\n" \
   /* Alignment is known to be at least 16-bit */ \
        "      tst   %[dst], #2\n" \
   "      ldrneh r4, [%[src]], #2\n" \
   "      strneh r4, [%[dst]], #2\n" \
   "      subne  %[count], %[count], #1\n" \
   /* Now destination address is 32-bit aligned, still need to check whether */ \
   /* source is 32-bit aligned or not */ \
   "      tst   %[src], #2\n" \
   "      bne   3f\n" \
   /* Both destination and source are 32-bit aligned */ \
   "      cmp   %[count], #8\n" \
   "      blt   2f\n" \
   "      tst   %[dst], #4\n" \
   "      ldrne r4, [%[src]], #4\n" \
   "      strne r4, [%[dst]], #4\n" \
   "      subne %[count], %[count], #2\n" \
   "      tst   %[dst], #8\n" \
   "      ldmneia %[src]!, {r4-r5}\n" \
   "      stmneia %[dst]!, {r4-r5}\n" \
   "      subne %[count], %[count], #4\n" \
   /* Destination address is 128-bit aligned, source address is 32-bit aligned */ \
   "1:    subs  %[count], %[count], #8\n" \
   "      ldmgeia %[src]!, {r4-r7}\n" \
   "      stmgeia %[dst]!, {r4-r7}\n" \
   "      bge   1b\n" \
   "      add   %[count], %[count], #8\n" \
   /* Copy up to 3 remaining aligned 32-bit values */ \
   "2:    tst   %[count], #4\n" \
   "      ldmneia %[src]!, {r4-r5}\n" \
   "      stmneia %[dst]!, {r4-r5}\n" \
   "      tst   %[count], #2\n" \
   "      ldrne r4, [%[src]], #4\n" \
   "      strne r4, [%[dst]], #4\n" \
   "      and  %[count], %[count], #1\n" \
   "      b      6f\n" \
   /* Destination is 32-bit aligned, but source is only 16-bit aligned */ \
   "3:    cmp   %[count], #8\n" \
   "      blt   5f\n" \
   "      tst   %[dst], #4\n" \
   "      ldrneh r4, [%[src]], #2\n" \
   "      ldrneh r5, [%[src]], #2\n" \
   "      orrne  r4, r4, r5, asl #16\n" \
   "      strne r4, [%[dst]], #4\n" \
   "      subne %[count], %[count], #2\n" \
   "      tst   %[dst], #8\n" \
   "      ldrneh r4, [%[src]], #2\n" \
   "      ldrne  r5, [%[src]], #4\n" \
   "      ldrneh r6, [%[src]], #2\n" \
   "      orrne  r4, r4, r5, asl #16\n" \
   "      movne  r5, r5, lsr #16\n" \
   "      orrne  r5, r5, r6, asl #16\n" \
   "      stmneia %[dst]!, {r4-r5}\n" \
   "      subne %[count], %[count], #4\n" \
   /* Destination is 128-bit aligned, but source is only 16-bit aligned */ \
   "4:    subs  %[count], %[count], #8\n" \
   "      ldrgeh r4, [%[src]], #2\n" \
   "      ldmgeia %[src]!, {r5-r7}\n" \
   "      ldrgeh %[dummy0], [%[src]], #2\n" \
   "      orrge r4, r4, r5, asl #16\n" \
   "      movge r5, r5, lsr #16\n" \
   "      orrge r5, r5, r6, asl #16\n" \
   "      movge r6, r6, lsr #16\n" \
   "      orrge r6, r6, r7, asl #16\n" \
   "      movge r7, r7, lsr #16\n" \
   "      orrge r7, r7, %[dummy0], asl #16\n" \
   "      stmgeia %[dst]!, {r4-r7}\n" \
   "      bge    4b\n" \
   "      add    %[count], %[count], #8\n" \
   /* Copy up to 6 remaining 16-bit values (to 32-bit aligned destination) */ \
   "5:    subs   %[count], %[count], #2\n" \
   "      ldrgeh r4, [%[src]], #2\n" \
   "      ldrgeh r5, [%[src]], #2\n" \
   "      orrge  r4, r4, r5, asl #16\n" \
   "      strge  r4, [%[dst]], #4\n" \
   "      bge    5b\n" \
   "      add    %[count], %[count], #2\n" \
   /* Copy the last remaining 16-bit value if any */ \
   "6:    subs   %[count], %[count], #1\n" \
   "      ldrgeh r4, [%[src]], #2\n" \
   "      strgeh r4, [%[dst]], #2\n" \
   "\n" \
   : [dst] "+&r" (dst),  [src] "+&r" (src), [count] "+&r" (count), [dummy0] "=&r" (dummy0) \
   : \
   : "r4", "r5", "r6", "r7", "cc", "memory" \
    ); _dst; \
})
#else
/*
 * memset() repeats the low byte of its value argument.  It cannot be used
 * as a fallback for the ARM routines above when the requested 16/32-bit
 * value is non-zero (the renderer uses memset32() for packed colours).
 */
#if defined(PS2) && defined(__GNUC__)
/* Keep the R5900 loop out of line: this helper has many scanline call sites,
 * and duplicating it costs more instruction cache than a function call. */
static __attribute__((noinline, noclone))
#else
static __inline__
#endif
void *s9x_memset32(void *dst, uint32_t value, size_t count)
{
   uint32_t *out = (uint32_t *)dst;

#if defined(PS2) && defined(__GNUC__)
   while (count && ((uintptr_t)out & 15u))
   {
      *out++ = value;
      count--;
   }

   if (count >= 4)
   {
      uint64_t packed = ((uint64_t)value << 32) | value;
      size_t blocks = count >> 2;

      count &= 3;
      __asm__ __volatile__ (
         ".set   push\n"
         ".set   noreorder\n"
         "pcpyld %[packed], %[packed], %[packed]\n"
         "1:\n"
         "sq     %[packed], 0(%[out])\n"
         "addiu  %[blocks], %[blocks], -1\n"
         "bnez   %[blocks], 1b\n"
         "addiu  %[out], %[out], 16\n"
         ".set   pop\n"
         : [out] "+&r" (out), [blocks] "+&r" (blocks),
           [packed] "+&r" (packed)
         :
         : "memory"
      );
   }
#endif

   while (count--)
      *out++ = value;

   return dst;
}

static __inline__ void *s9x_memset16(void *dst, uint16_t value, size_t count)
{
   uint16_t *out = (uint16_t *)dst;

   while (count--)
      *out++ = value;

   return dst;
}

#define memset32(_dst, _c, _count) s9x_memset32((_dst), (_c), (_count))
#define memset16(_dst, _c, _count) s9x_memset16((_dst), (_c), (_count))
#define memcpy32(_dst, _src, _count) memcpy(_dst, _src, (_count)<<2)
#define memcpy16(_dst, _src, _count) memcpy(_dst, _src, (_count)<<1)
#endif

#endif
