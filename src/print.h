/*****************************************************************************
 *          
 *          START EDITOR:  print functions & definitions 
 *          Authors:              - Alex Winter,  <eterno.despierto@gmail.com>
 *                                    -
 *
 *          Date:                  02.2013
 *          Version:              1.0.0.1
 *
 *****************************************************************************/

#ifndef _PRINT_H_
#define _PRINT_H_

#define GPRINTF_LOG_OK
#define GPRINTF_ERR_OK
#define GPRINTF_DBG_OK
#define GPRINTF_WRN_OK

//WARNING: please write name of function in 20 simbols or increase an offset

#ifdef GPRINTF_LOG_OK
#define gprint_inf                   g_print
#else  /* GPRINTF_LOG_OK */
#define gprint_inf(fmt, args...)
#endif  /* GPRINTF_LOG_OK */

#ifdef GPRINTF_LOG_OK
#define gprint_log(fmt, args...) g_print("%s: " fmt "\n", __FUNCTION__, ## args)
#else  /* GPRINTF_LOG_OK */
#define gprint_log(fmt, args...)
#endif  /* GPRINTF_LOG_OK */

#ifdef GPRINTF_DBG_OK
#define gprint_dbg(fmt, args...) g_print("[dbg] %20s: " fmt "\n", __FUNCTION__, ## args)
#else  /* GPRINTF_DBG_OK */
#define gprint_dbg(fmt, args...)
#endif  /* GPRINTF_DBG_OK */

#ifdef GPRINTF_WRN_OK
#define gprint_wrn(fmt, args...) g_print("[wrn] %20s: " fmt "\n", __FUNCTION__, ## args)
#else  /* GPRINTF_WRN_OK */
#define gprint_wrn(fmt, args...)
#endif  /* GPRINTF_WRN_OK */

#ifdef GPRINTF_ERR_OK
#define gprint_err(fmt, args...) g_print("[err] %20s: " fmt "\n", __FUNCTION__, ## args)
#else  /* GPRINTF_ERR_OK */
#define gprint_err(fmt, args...)
#endif  /* GPRINTF_ERR_OK */


#endif /*_PRINT_H_*/

