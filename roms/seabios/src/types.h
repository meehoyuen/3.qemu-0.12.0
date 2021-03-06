// Basic type definitions for X86 cpus.
//
// Copyright (C) 2008,2009  Kevin O'Connor <kevin@koconnor.net>
//
// This file may be distributed under the terms of the GNU LGPLv3 license.
#ifndef __TYPES_H
#define __TYPES_H

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;
typedef signed long long s64;
typedef u32 size_t;

union u64_u32_u {
    struct { u32 hi, lo; };
    u64 val;
};

#ifdef MANUAL_NO_JUMP_TABLE
# define default case 775324556: asm(""); default
#endif

#ifdef WHOLE_PROGRAM
# define __VISIBLE __attribute__((externally_visible))
#else
# define __VISIBLE
#endif

#define UNIQSEC __FILE__ "." __stringify(__LINE__)

#define __ASM(code) asm(".section .text.asm." UNIQSEC "\n\t" code)

#if MODE16 == 1
// Notes a function as externally visible in the 16bit code chunk.
# define VISIBLE16 __VISIBLE
// Notes a function as externally visible in the 32bit code chunk.
# define VISIBLE32
// Designate a variable as (only) visible to 16bit code.
# define VAR16 __section(".data16." UNIQSEC)
// Designate a variable as visible to 16bit, 32bit, and assembler code.
# define VAR16VISIBLE VAR16 __VISIBLE
// Designate a variable as externally visible (in addition to all internal code).
# define VAR16EXPORT __section(".data16.export." UNIQSEC) __VISIBLE
// Designate a variable at a specific 16bit address
# define VAR16FIXED(addr) __aligned(1) __VISIBLE __section(".fixedaddr." __stringify(addr))
// Designate a 32bit variable also available in 16bit "big real" mode.
# define VAR32VISIBLE __section(".discard.var32." UNIQSEC) __VISIBLE __weak
// Designate top-level assembler as 16bit only.
# define ASM16(code) __ASM(code)
// Designate top-level assembler as 32bit only.
# define ASM32(code)
#else
# define VISIBLE16
# define VISIBLE32 __VISIBLE
# define VAR16 __section(".discard.var16." UNIQSEC)
# define VAR16VISIBLE VAR16 __VISIBLE __weak
# define VAR16EXPORT VAR16VISIBLE
# define VAR16FIXED(addr) VAR16VISIBLE
# define VAR32VISIBLE __VISIBLE
# define ASM16(code)
# define ASM32(code) __ASM(code)
#endif

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define FIELD_SIZEOF(t, f) (sizeof(((t*)0)->f))
#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
#define DIV_ROUND_CLOSEST(x, divisor)({                 \
            typeof(divisor) __divisor = divisor;        \
            (((x) + ((__divisor) / 2)) / (__divisor));  \
        })
#define ALIGN(x,a)              __ALIGN_MASK(x,(typeof(x))(a)-1)
#define __ALIGN_MASK(x,mask)    (((x)+(mask))&~(mask))
#define ALIGN_DOWN(x,a)         ((x) & ~((typeof(x))(a)-1))
#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})

#define NULL ((void*)0)

#define __weak __attribute__((weak))
#define __section(S) __attribute__((section(S)))

#define PACKED __attribute__((packed))
#define __aligned(x) __attribute__((aligned(x)))

#define barrier() __asm__ __volatile__("": : :"memory")

#define noinline __attribute__((noinline))
#define __always_inline inline __attribute__((always_inline))

#define __stringify_1(x)        #x
#define __stringify(x)          __stringify_1(x)

#endif // types.h
