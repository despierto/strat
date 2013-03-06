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
    GTK_WIDGET_TYPE_TABLE,
    GTK_WIDGET_TYPE_CELL,       //actually it it a container of widget in the table    
} GTK_WIDGET_TYPE;

typedef enum
{
    GTK_BOX_PACK_TYPE_NONE = 0,
    GTK_BOX_PACK_TYPE_START,
    GTK_BOX_PACK_TYPE_END,
} GTK_BOX_PACK_TYPE;

typedef enum
{
    GTK_TABLE_PACKING_TYPE_DEFAULT = 0,
    GTK_TABLE_PACKING_TYPE_EXTENDED,
} GTK_TABLE_PACKING_TYPE;

typedef enum
{
    GTK_BUTTON_TYPE_EMPTY = 0,
    GTK_BUTTON_TYPE_LABEL,
    GTK_BUTTON_TYPE_MNEMONIC,
    GTK_BUTTON_TYPE_MIXED,
    GTK_BUTTON_TYPE_TOGGLE,    
    GTK_BUTTON_TYPE_TOGGLE_LABEL,        
    GTK_BUTTON_TYPE_TOGGLE_MNEMONIC,            
    GTK_BUTTON_TYPE_TOGGLE_MIXED,    
} GTK_BUTTON_TYPE;

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
    GTK_BUTTON_TYPE     button_type;

    U32     pos_x;
    U32     pos_y; 
    U32     width;
    U32     hight;

    PSTR    caption;
    PSTR    icon_file;

    PSTR    exit_on_type;

    PTR     ptr_pressed;
    PTR     ptr_released;
    PTR     ptr_clicked;
    PTR     ptr_enter;
    PTR     ptr_leave;
    PTR     ptr_activate;
    PTR     ptr_toggled;    

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
    BOOL            same_size;    //width for hbox & hight for vbox
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

typedef struct _GTK_TABLE_SETTINGS_
{
    U32             rows;
    U32             columns;
    BOOL            same_size;
    U32             spacing_rows;
    U32             spacing_columns;

}GTK_TABLE_SETTINGS, *PGTK_TABLE_SETTINGS;

typedef struct _GTK_CELL_SETTINGS_
{
    GTK_TABLE_PACKING_TYPE packing_type;

    U32             attach_left;
    U32             attach_right;
    U32             attach_top;
    U32             attach_bottom;    
    GtkAttachOptions attach_option_x;        
    GtkAttachOptions attach_option_y;        
    U32             padding_x;
    U32             padding_y;
    U32             spacing_row;
    U32             spacing_column;

}GTK_CELL_SETTINGS, *PGTK_CELL_SETTINGS;


#endif /*_GTK_IFACE_TYPES_H_*/

