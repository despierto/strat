/*****************************************************************************
 *          
 *          START EDITOR:  print functions & definitions 
 *
 *****************************************************************************/

#ifndef _PRINT_H_
#define _PRINT_H_

#include "types.h"

#define GPRINTF_LOG_OK
#define GPRINTF_ERR_OK
#define GPRINTF_DBG_OK


#ifdef GPRINTF_LOG_OK
#define gprint_log(fmt, args...) g_print("%s: " fmt "\n", __FUNCTION__, ## args)
#else  /* GPRINTF_LOG_OK */
#define gprint_log(fmt, args...)
#endif  /* GPRINTF_LOG_OK */

#ifdef GPRINTF_DBG_OK
#define gprint_dbg(fmt, args...) g_print("%s:[dbg] " fmt "\n", __FUNCTION__, ## args)
#else  /* GPRINTF_LOG_OK */
#define gprint_dbg(fmt, args...)
#endif  /* GPRINTF_LOG_OK */

#ifdef GPRINTF_ERR_OK
#define gprint_err(fmt, args...) g_print("%s:[err] " fmt "\n", __FUNCTION__, ## args)
#else  /* GPRINTF_LOG_OK */
#define gprint_err(fmt, args...)
#endif  /* GPRINTF_LOG_OK */


#endif /*_PRINT_H_*/
