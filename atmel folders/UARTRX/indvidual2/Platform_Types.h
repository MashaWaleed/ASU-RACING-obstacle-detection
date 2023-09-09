/*
 * Platform_Types.h
 *
 *  Created on: July 21, 2023
 *      Author: MohamedWaleed
 */


#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_


#ifndef _Bool
#define _Bool unsigned char
#endif

#define CPU_TYPE                   CPU_TYPE_32
#define CPU_BIT_ORDER              MSB_FIRST
#define CPU_BYTE_ORDER             HIGH_BYTE_FIRST

#ifndef FALSE
#define FALSE                      (boolean)false
#endif

#ifndef TRUE
#define TRUE                       (boolean)true
#endif


// BOOLEAN TYPE
typedef _Bool                           boolean;

// CHAR TYPE 8-BIT
typedef unsigned char                   u8;
typedef signed char                     s8;
typedef volatile unsigned char          vu8;
typedef volatile signed char            vs8;

// SHORT TYPE 16-BIT
typedef unsigned short                  u16;
typedef signed short                    s16;
typedef volatile unsigned short         vu16;
typedef volatile signed short           vs16;

// INT TYPE 32-BIT
typedef unsigned int                    u32;
typedef signed int                      s32;
typedef volatile unsigned int           vu32;
typedef volatile signed int             vs32;

// LONG LONG TYPE 64-BIT
typedef signed long long                s64;
typedef unsigned long long              u64;
typedef volatile unsigned long long     vu64;
typedef volatile signed long long       vs64;

typedef float                           f32;
typedef double						    f64;

typedef volatile float                  vf32;
typedef volatile double					vf64;

#endif /* PLATFORM_TYPES_H_ */