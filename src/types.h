/*****************************************************************************
 *          
 *          START EDITOR:  types definitions 
 *          Authors:              - Alex Winter,  <eterno.despierto@gmail.com>
 *                                    -
 *
 *          Date:                  02.2013
 *          Version:              1.0.0.1
 *
 *****************************************************************************/

#ifndef _TYPES_H_
#define _TYPES_H_

#include "print.h"


#define SUCCESS         (0)
#define FAILURE         (1)

#ifndef TRUE
#define TRUE            (1)
#endif
#define FALSE           (0)
#define NULLP           (void *)0
#ifndef NULL
#define NULL            (0)
#endif

#define INLINE          inline

typedef char            STR, *PSTR;

typedef signed char     S8, *PS8;
typedef signed short    S16, *PS16;
typedef int             S32, *PS32;
typedef long long int   S64, *PS64;

typedef unsigned char   U8, *PU8;
typedef unsigned short  U16, *PU16;
typedef unsigned int    U32, *PU32;
typedef long long unsigned int U64, *PU64;

typedef volatile unsigned char  VU8, *PV8;
typedef volatile unsigned short VU16, *PVU16;
typedef volatile unsigned int   VU32, *PVU32;
typedef volatile long long unsigned int VU64, *PV64;


typedef void*           PTR;
typedef U32             BOOL;
typedef U32             BIT_FIELD;


#ifndef MAX
#define MAX(x, y)       ((x) >= (y) ? (x) : (y))
#endif
#ifndef MIN
#define MIN(x, y)       ((x) <= (y) ? (x) : (y))
#endif
#define ROUND(x, dx)    (((x) + ((dx) - 1) ) & ~((dx) - 1))

#define __align(x)      __attribute__((aligned(x)))

typedef enum
{
  NUM_TYPE_DEC = 0,
  NUM_TYPE_HEX_L,
  NUM_TYPE_HEX_H,  
  NUM_TYPE_MASK,    
} NUM_TYPE;


static inline void _AssertHandler(U32 rc, const S8 *filename, U32 line)
{
    gprint_log("\r\n---- ASSERT---\r\n");
    gprint_log("         RC:0x%08x", rc);
    gprint_log("       File:%s", filename);
    gprint_log("       Row :%d", line);   
}

#define _ASSERT(x) if ((U32)x == 0) { _AssertHandler ((U32)x, __FILE__, __LINE__); while (1);}


#endif /*_TYPES_H_*/

