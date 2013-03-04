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

#define GTK_EVENT_TYPE_EVENT            "event"
#define GTK_EVENT_TYPE_BUTTON_PRESS     "button_press_event"
#define GTK_EVENT_TYPE_BUTTON_RELEASE   "button_release_event"
#define GTK_EVENT_TYPE_SCROLL           "scroll_event"
#define GTK_EVENT_TYPE_MOTION_NOTIFY    "motion_notify_event"
#define GTK_EVENT_TYPE_EXPOSE           "expose_event"
#define GTK_EVENT_TYPE_KEY_PRESS        "key_press_event"
#define GTK_EVENT_TYPE_KEY_RELEASE      "key_release_event"
#define GTK_EVENT_TYPE_ENTER_NOTIFY     "enter_notify_event"
#define GTK_EVENT_TYPE_LEAVE_NOTIFY     "leave_notify_event"
#define GTK_EVENT_TYPE_CONFIGURE        "configure_event"
#define GTK_EVENT_TYPE_FOCUS_IN         "focus_in_event"
#define GTK_EVENT_TYPE_FOCUS_OUT        "focus_out_event"
#define GTK_EVENT_TYPE_MAC              "map_event"
#define GTK_EVENT_TYPE_UNMAP            "unmap_event"
#define GTK_EVENT_TYPE_PROPERTY_NOTIFY  "property_notify_event"
#define GTK_EVENT_TYPE_SELECTION_CLEAR  "selection_clear_event"
#define GTK_EVENT_TYPE_SELECTION_REQUEST "selection_request_event"
#define GTK_EVENT_TYPE_SELECTION_NOTIRY "selection_notify_event"
#define GTK_EVENT_TYPE_PROXIMITY_IN     "proximity_in_event"
#define GTK_EVENT_TYPE_PROXIMITY_OUT    "proximity_out_event"
#define GTK_EVENT_TYPE_VISIBILITY_NOTIFY "visibility_notify_event"
#define GTK_EVENT_TYPE_CLIENT           "client_event"
#define GTK_EVENT_TYPE_NO_EXPOSE        "no_expose_event"
#define GTK_EVENT_TYPE_WINDOW_STATE     "window_state_event"





#endif /*_GTK_IFACE_WRAP_H_*/

