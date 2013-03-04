/*****************************************************************************
 *          
 *          START EDITOR:  gtk interface
 *
 *****************************************************************************/

#ifndef _GTK_IFACE_H_
#define _GTK_IFACE_H_

#include "global.h"



//gtk type for storing widget content
typedef GtkWidget   GTK_WIDGET, *PGTK_WIDGET;
typedef GdkEvent    GTK_EVENT, *PGTK_EVENT;
typedef gpointer    GPTR;

#define GTK_OBJ(x)     G_OBJECT (x)
#define GTK_CB(x)      G_CALLBACK(x)
#define GTK_CTR(x)      GTK_CONTAINER(x)

#define GTK_WINDOW_TYPE_TOPLEVEL    GTK_WINDOW_TOPLEVEL


#define GTK_BUTTON_TYPE_CLECKED     "clicked"


void        gtkInit(S32 argc, PSTR argv[]);
PGTK_WIDGET gtkNewWindow(PTR del_event, PSTR del_event_caption, PTR destroy, PSTR destroy_caption, U32 type);
void        gtkStartApplication(void);
PGTK_WIDGET gtkAddButton(PGTK_WIDGET widget, PTR ptr, PSTR caption, PSTR type, U32 exit);
void        gtkShowWindow(PGTK_WIDGET widget);
void gtkSetupWindowView(PGTK_WIDGET widget, U32 border_width);

#endif /*_GTK_IFACE_H_*/

