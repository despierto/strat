/*****************************************************************************
 *          
 *          START EDITOR:  gtk interface wrappers
 *          Authors:              - Alex Winter,  <eterno.despierto@gmail.com>
 *                                    -
 *
 *          Date:                  02.2013
 *          Version:              1.0.0.1
 *
 *****************************************************************************/

#ifndef _GTK_IFACE_WRAP_H_
#define _GTK_IFACE_WRAP_H_

#include <gtk/gtk.h>
#include "gtkenums.h"


//redefinitions of subs
#ifndef G_OBJECT
#define G_OBJECT(x)             G_OBJECT (x)
#endif
#ifndef G_CALLBACK
#define G_CALLBACK(x)           G_CALLBACK (x)
#endif
#ifndef GTK_CONTAINER
#define GTK_CONTAINER(x)        GTK_CONTAINER (x)
#endif
#ifndef GTK_WINDOW
#define GTK_WINDOW(x)           GTK_WINDOW (x)
#endif
#ifndef GTK_FIXED
#define GTK_FIXED(x)            GTK_FIXED (x)
#endif


//redefinitions of gtk type for storing widget content
typedef gpointer        GPTR;
typedef GtkWidget       GTK_WIDGET,         *PGTK_WIDGET;
typedef GdkEvent        GTK_EVENT,          *PGTK_EVENT;
typedef GdkPixbuf       GTK_PIXBUF,         *PGTK_PIXBUF;
typedef GError          GTK_ERROR,          *PGTK_ERROR;
typedef gchar           GTK_CHAR,           *PGTK_CHAR;
typedef GtkWindowType   GTK_WINDOW_TYPE,   *PGTK_WINDOW_TYPE;



//collecting types for button
#define GTK_BUTTON_TYPE_NONE        NULL
#define GTK_BUTTON_TYPE_PRESSED     "pressed"
#define GTK_BUTTON_TYPE_RELEASED    "released"
#define GTK_BUTTON_TYPE_CLICKED     "clicked"
#define GTK_BUTTON_TYPE_ENTER       "enter"
#define GTK_BUTTON_TYPE_LEAVE       "leave"
#define GTK_BUTTON_TYPE_ACTIVE      "activate"

//collecting types for events
#define GTK_EVENT_TYPE_DELETE       "delete_event"
#define GTK_EVENT_TYPE_DESTROY      "destroy"





#endif /*_GTK_IFACE_WRAP_H_*/

