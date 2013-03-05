/*****************************************************************************
 *          
 *          START EDITOR:  gtk interface local types
 *          Authors:              - Alex Winter,  <eterno.despierto@gmail.com>
 *                                    -
 *
 *          Date:                  02.2013
 *          Version:              1.0.0.1
 *
 *****************************************************************************/

#ifndef _GTK_IFACE_TYPES_H_
#define _GTK_IFACE_TYPES_H_

#include "gtk_iface_wrap.h"
#include "types.h"

typedef enum
{
    GTK_WIDGET_TYPE_NONE = 0,
    GTK_WIDGET_TYPE_WINDOW,
    GTK_WIDGET_TYPE_BUTTON,
    GTK_WIDGET_TYPE_FRAME,
    GTK_WIDGET_TYPE_LABEL,
    GTK_WIDGET_TYPE_HBOX,
    GTK_WIDGET_TYPE_VBOX,    
    GTK_WIDGET_TYPE_HSEPARATOR,
    GTK_WIDGET_TYPE_VSEPARATOR,    
} GTK_WIDGET_TYPE;


typedef enum
{
    GTK_BOX_PACK_TYPE_NONE = 0,
    GTK_BOX_PACK_TYPE_START,
    GTK_BOX_PACK_TYPE_END,
} GTK_BOX_PACK_TYPE;


typedef struct _GTK_WINDOW_SETTINGS_
{
    GtkWindowType       window_type;
    GtkWindowPosition   position;

    U32     border_width;
    U32     width;
    U32     hight;
    
    PSTR    title;
    PSTR    icon_filename;

    PTR     ptr_delete_event;
    PTR     ptr_destroy;

}GTK_WINDOW_SETTINGS, *PGTK_WINDOW_SETTINGS;

typedef struct _GTK_BUTTON_SETTINGS_
{
    U32     pos_x;
    U32     pos_y; 
    U32     width;
    U32     hight;

    PSTR    caption;
//    PSTR    type;

    PSTR    exit_on_type;

    PTR     ptr_pressed;
    PTR     ptr_released;
    PTR     ptr_clicked;
    PTR     ptr_enter;
    PTR     ptr_leave;
    PTR     ptr_activate;

}GTK_BUTTON_SETTINGS, *PGTK_BUTTON_SETTINGS;

typedef struct _GTK_FRAME_SETTINGS_
{
    PSTR    caption;

}GTK_FRAME_SETTINGS, *PGTK_FRAME_SETTINGS;

typedef struct _GTK_SEPARATOR_SETTINGS_
{
    GTK_WIDGET_TYPE    sepatator_type;
    U32     width;
    U32     hight;    

}GTK_SEPARATOR_SETTINGS, *PGTK_SEPARATOR_SETTINGS;

typedef struct _GTK_BOX_SETTINGS_
{
    PSTR            caption;
    GTK_WIDGET_TYPE box_type;
    BOOL            set_same_length;    //width for hbox & hight for vbox
    U32             spacing;

}GTK_BOX_SETTINGS, *PGTK_BOX_SETTINGS;

typedef struct _GTK_LABEL_SETTINGS_
{
    PSTR    caption;
   
    U32     pos_x;
    U32     pos_y;    
 
    GF32    aling_x;    // left =0..1=right
    GF32    aling_y;    // top =0..1=buttom

}GTK_LABEL_SETTINGS, *PGTK_LABEL_SETTINGS;




#endif /*_GTK_IFACE_TYPES_H_*/

