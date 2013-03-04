/*****************************************************************************
 *          
 *          START EDITOR:  gtk interface
 *          Authors:              - Alex Winter,  <eterno.despierto@gmail.com>
 *                                    -
 *
 *          Date:                  02.2013
 *          Version:              1.0.0.1
 *
 *****************************************************************************/

#ifndef _GTK_IFACE_H_
#define _GTK_IFACE_H_

#include "gtk_iface_types.h"

void        gtkInit(S32 argc, PSTR argv[]);
void        gtkShowWindow(PGTK_WIDGET widget);
void        gtkShowAllInWindow(PGTK_WIDGET widget);
void        gtkStartApplication(void);

PGTK_WIDGET gtkNewWindow(PGTK_WINDOW_SETTINGS settings);
PGTK_WIDGET gtkNewButton(PGTK_WIDGET widget, GTK_WIDGET_TYPE widget_type, PGTK_BUTTON_SETTINGS settings);
PGTK_WIDGET gtkNewFrame(PGTK_WIDGET widget, GTK_WIDGET_TYPE widget_type, PGTK_FRAME_SETTINGS settings);
PGTK_WIDGET gtkNewLabel(PGTK_WIDGET widget, GTK_WIDGET_TYPE widget_type, PGTK_LABEL_SETTINGS settings);


void        gtkSetupWindowView(PGTK_WIDGET widget, GTK_WIDGET_TYPE widget_type, PGTK_WINDOW_SETTINGS settings);
PGTK_PIXBUF gtkCreatePixbuf(const PSTR filename);

void        gtkSetNum(PGTK_WIDGET widget, GTK_WIDGET_TYPE widget_type, U32 number, NUM_TYPE number_type, PSTR mask);
void        gtkSetText(PGTK_WIDGET widget, GTK_WIDGET_TYPE widget_type, PSTR text);




#endif /*_GTK_IFACE_H_*/

