/*****************************************************************************
 *          
 *          START EDITOR:  global definitions 
 *
 *****************************************************************************/

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "types.h"
#include "print.h"



static inline void _AssertHandler(U32 rc, const S8 *filename, U32 line)
{
    gprint_log("\r\n---- ASSERT---\r\n\r\n");
    gprint_log("         RC:0x%08x\r\n", rc);
    gprint_log("       File:%s\r\n", filename);
    gprint_log("       Row :%d\r\n", line);   
}

#define _ASSERT(x) if ((U32)x == 0) { _AssertHandler ((U32)x, __FILE__, __LINE__); while (1);}




#endif /*_GLOBAL_H_*/
