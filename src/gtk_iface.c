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

#include "gtk_iface.h"
#include "print.h"

PGTK_WIDGET gtkNewMixedButton(PSTR caption, PSTR icon_file);


/****************************************************************************************
 *           Events
 ****************************************************************************************/
 
void gtkInit(S32 argc, PSTR argv[])
{
    gprint_dbg("argc=%d argv=%s", (U32)argc, argv);
    gtk_init(&argc, &argv);
    
    return;
}

void gtkShowWindow(PGTK_WIDGET widget)
{
    gprint_dbg("window=   0x%x:", (U32)widget);
    _ASSERT(widget);     
    gtk_widget_show(widget);

    return;
}

void gtkShowAllInWindow(PGTK_WIDGET widget)
{
    gprint_dbg("widget=   0x%x:", (U32)widget);
    _ASSERT(widget); 
    gtk_widget_show_all(widget);

    return;
}

void gtkStartApplication(void)
{
    gprint_log("start GUI");    
    gtk_main();
    gprint_log("stop GUI");    
    
    return;
}


/****************************************************************************************
 *           New components
 ****************************************************************************************/
 
PGTK_WIDGET gtkNewWindow(PGTK_WINDOW_SETTINGS settings)
{
    PGTK_WIDGET     widget;
    
    _ASSERT(settings); 
    widget = gtk_window_new(settings->window_type);
    
    gprint_dbg("window=   0x%x: title=<%s> w=%d h=%d bw=%d pos=%d", 
        (U32)widget, settings->title, settings->width, settings->hight, settings->border_width, (U32)settings->position);
    gprint_dbg("window=   0x%x: type=%d PTR: D(%X) DE(%X) icon_file=<%s>", 
            (U32)widget, settings->window_type, (U32)settings->ptr_destroy, (U32)settings->ptr_delete_event, settings->icon_filename);
    _ASSERT(widget);

    if (settings->ptr_delete_event)
        gtkConnectEventCb(widget, GTK_EVENT_TYPE_DELETE, settings->ptr_delete_event);
    if (settings->ptr_destroy)
        gtkConnectEventCb(widget, GTK_EVENT_TYPE_DESTROY, settings->ptr_destroy);

    gtk_window_set_title(GTK_WINDOW(widget), settings->title);
    gtk_window_set_default_size(GTK_WINDOW(widget), settings->width, settings->hight);
    gtk_window_set_position(GTK_WINDOW(widget), settings->position);
    gtk_container_set_border_width (GTK_CONTAINER (widget), settings->border_width);

    if (settings->icon_filename)
        gtk_window_set_icon(GTK_WINDOW(widget), gtkCreatePixbuf(settings->icon_filename));

    return widget;
}

PGTK_WIDGET gtkNewFrame(PGTK_WIDGET widget, 
                            GTK_WIDGET_TYPE widget_type, 
                            PGTK_FRAME_SETTINGS settings)
{
    PGTK_WIDGET     frame = gtk_fixed_new();

    _ASSERT(settings);
    gprint_dbg("frame=    0x%x: widget=0x%x widget_type=%d caption=<%s>", (U32)frame, (U32)widget, widget_type, settings->caption);

    _ASSERT(frame);

    gtk_container_add (GTK_CONTAINER (widget), frame);
    
    return frame;
}

PGTK_WIDGET gtkNewBox(  PGTK_WIDGET widget, 
                            GTK_WIDGET_TYPE widget_type, 
                            PGTK_BOX_SETTINGS settings)
{
    PGTK_WIDGET     box = NULL;

    _ASSERT(settings);

    if (settings->box_type == GTK_WIDGET_TYPE_HBOX)
        box = gtk_hbox_new (FALSE, 0);
    else if (settings->box_type == GTK_WIDGET_TYPE_VBOX)
        box = gtk_vbox_new (FALSE, 0);
    else
        gprint_err(" undefined widget type=%d", widget_type);

    gprint_dbg("box=      0x%x: widget=0x%x widget_type=%d same_length=%d spacing=%d", 
                            (U32)box, (U32)widget, widget_type, settings->same_size, settings->spacing);
    _ASSERT(box);

    if (widget_type == GTK_WIDGET_TYPE_WINDOW)
        gtk_container_add (GTK_CONTAINER (widget), box);
    else if ((widget_type == GTK_WIDGET_TYPE_VBOX) || (widget_type == GTK_WIDGET_TYPE_VBOX))
         gtkAddToBox(widget, widget_type, GTK_BOX_PACK_TYPE_START, box, settings->box_type, FALSE, FALSE, 0);

    return box;
}

PGTK_WIDGET gtkNewLabel( PGTK_WIDGET widget, 
                            GTK_WIDGET_TYPE widget_type, 
                            PGTK_LABEL_SETTINGS settings)
{
    PGTK_WIDGET     label;

    _ASSERT(settings);
    label = gtk_label_new(settings->caption);
    
    gprint_dbg("label=    0x%x: widget=0x%x widget_type=%d caption=<%s> x=%d y=%d", 
        (U32)label, (U32)widget, widget_type, settings->caption,  settings->pos_x, settings->pos_y);
    _ASSERT(label);

    gtk_misc_set_alignment (GTK_MISC (label), settings->aling_x, settings->aling_y);

    if (widget_type == GTK_WIDGET_TYPE_FRAME)
        gtk_fixed_put(GTK_FIXED(widget), label, settings->pos_x, settings->pos_y);
    else if ((widget_type == GTK_WIDGET_TYPE_HBOX) || (widget_type == GTK_WIDGET_TYPE_VBOX))
        gtkAddToBox(widget, widget_type, GTK_BOX_PACK_TYPE_START, label, GTK_WIDGET_TYPE_LABEL, FALSE, FALSE, 0);
    
    return label;
}

PGTK_WIDGET gtkNewTable( PGTK_WIDGET widget, 
                            GTK_WIDGET_TYPE widget_type, 
                            PGTK_TABLE_SETTINGS settings)
{
    PGTK_WIDGET table;
    
    _ASSERT(settings);
    table = gtk_table_new(settings->rows,  settings->columns, settings->same_size);
    
    gprint_dbg("table=    0x%x: widget=0x%x widget_type=%d rows=%d columns=%d same_size=%d", 
        (U32)table, (U32)widget, widget_type, settings->rows,  settings->columns, settings->same_size);
    _ASSERT(table);

    if (settings->spacing_rows)
        gtk_table_set_row_spacings(GTK_TABLE(table), settings->spacing_rows);
    if (settings->spacing_columns)
        gtk_table_set_col_spacings(GTK_TABLE(table), settings->spacing_columns);

    if ((widget_type == GTK_WIDGET_TYPE_HBOX) || (widget_type == GTK_WIDGET_TYPE_VBOX))
        gtkAddToBox(widget, widget_type, GTK_BOX_PACK_TYPE_START, table, GTK_WIDGET_TYPE_LABEL, FALSE, FALSE, 0);
    
    return table;
}

PGTK_WIDGET gtkNewSeparator(PGTK_WIDGET widget, 
                                GTK_WIDGET_TYPE widget_type, 
                                PGTK_SEPARATOR_SETTINGS settings)
{
    PGTK_WIDGET     separator = NULL;
    _ASSERT(settings);

    if (settings->sepatator_type == GTK_WIDGET_TYPE_HSEPARATOR)
        separator = gtk_hseparator_new();
    else if (settings->sepatator_type == GTK_WIDGET_TYPE_VSEPARATOR)
        separator = gtk_vseparator_new();
    else
        gprint_err(" undefined widget type=%d", widget_type);

    gprint_dbg("separator=0x%x: widget=0x%x widget_type=%d", 
                            (U32)separator, (U32)widget, widget_type);
    _ASSERT(separator);

    if (settings->width && settings->hight)
        gtk_widget_set_size_request(separator, settings->width, settings->hight);

    if (widget_type == GTK_WIDGET_TYPE_WINDOW)
        gtk_container_add (GTK_CONTAINER (widget), separator);
    else if ((widget_type == GTK_WIDGET_TYPE_HBOX) || (widget_type == GTK_WIDGET_TYPE_VBOX))
         gtkAddToBox(widget, widget_type, GTK_BOX_PACK_TYPE_START, separator, settings->sepatator_type, FALSE, FALSE, 5);
    
    return separator;
}


PGTK_WIDGET gtkNewButton(PGTK_WIDGET widget, 
                            GTK_WIDGET_TYPE widget_type, 
                            PGTK_BUTTON_SETTINGS settings)
{
    PGTK_WIDGET     button;
    _ASSERT(settings);

    switch (settings->button_type)
    {
        case GTK_BUTTON_TYPE_CLEAN:            
            button = gtk_button_new();
            break;
        case GTK_BUTTON_TYPE_LABEL:            
            button = gtk_button_new_with_label(settings->caption);
            break;
        case GTK_BUTTON_TYPE_MNEMONIC:            
            button = gtk_button_new_with_mnemonic(settings->caption);
            break;
        case GTK_BUTTON_TYPE_MIXED:            
            button = gtkNewMixedButton(settings->caption, settings->icon_file);
            break;
        default:
             gprint_wrn(" undefined button type=%d", settings->button_type);
            break;
    }
    _ASSERT(settings);

    
    gprint_dbg("button=   0x%x: widget=0x%x widget_type=%d caption=<%s> w=%d h=%d x=%d y=%d", 
                    (U32)button, (U32)widget, widget_type, settings->caption, settings->width, 
                    settings->hight, settings->pos_x, settings->pos_y);
    gprint_dbg("button=   0x%x: exit_type=<%s> PTR: A(%X) C(%X) E(%X) L(%X) P(%X) R(%X)", 
        (U32)button, settings->exit_on_type,
        (U32)settings->ptr_activate, (U32)settings->ptr_clicked, (U32)settings->ptr_enter, 
        (U32)settings->ptr_leave, (U32)settings->ptr_pressed, (U32)settings->ptr_released);
    _ASSERT(button);

    if (settings->ptr_activate)
        gtkConnectEventCb(button, GTK_BUTTON_STATE_TYPE_ACTIVE, settings->ptr_activate);
    if (settings->ptr_clicked)
        gtkConnectEventCb(button, GTK_BUTTON_STATE_TYPE_CLICKED, settings->ptr_clicked);
    if (settings->ptr_enter)
        gtkConnectEventCb(button, GTK_BUTTON_STATE_TYPE_ENTER, settings->ptr_enter);
    if (settings->ptr_leave)
        gtkConnectEventCb(button, GTK_BUTTON_STATE_TYPE_LEAVE, settings->ptr_leave);
    if (settings->ptr_pressed)
        gtkConnectEventCb(button, GTK_BUTTON_STATE_TYPE_PRESSED, settings->ptr_pressed);
    if (settings->ptr_released)
        gtkConnectEventCb(button, GTK_BUTTON_STATE_TYPE_RELEASED, settings->ptr_released);

    if (settings->exit_on_type)
        g_signal_connect_swapped (G_OBJECT (button), settings->exit_on_type, G_CALLBACK(gtk_widget_destroy), G_OBJECT (widget));

    if (settings->width && settings->hight)
        gtk_widget_set_size_request(button, settings->width, settings->hight);

    if (widget_type == GTK_WIDGET_TYPE_FRAME)
    {
        gtk_fixed_put(GTK_FIXED(widget), button, settings->pos_x, settings->pos_y);
    }
    else if (widget_type == GTK_WIDGET_TYPE_WINDOW)
    {
        gtk_container_add (GTK_CONTAINER (widget), button);
        gtk_widget_show (button);
    }
    else if ((widget_type == GTK_WIDGET_TYPE_HBOX) || (widget_type == GTK_WIDGET_TYPE_VBOX))
    {
        gtkAddToBox(widget, widget_type, GTK_BOX_PACK_TYPE_START, button, GTK_WIDGET_TYPE_BUTTON, FALSE, FALSE, 0);
    }
    
    return (PGTK_WIDGET)button;
}

PGTK_WIDGET gtkNewMixedButton(PSTR caption, PSTR icon_file)
{
    PGTK_WIDGET button;
    PGTK_WIDGET box;
    PGTK_WIDGET label;
    PGTK_WIDGET image;

    button = gtk_button_new();
    _ASSERT(button);   

    box = gtk_hbox_new (FALSE, 0);
    _ASSERT(box);  

    gtk_container_set_border_width (GTK_CONTAINER (box), 2);
    
    image = gtk_image_new_from_file (icon_file);
    _ASSERT(image);  

    label = gtk_label_new (caption);
    _ASSERT(label);  

    gtk_box_pack_start (GTK_BOX (box), image, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 3);
    gtk_widget_show (image);
    gtk_widget_show (label);

    gtk_container_add (GTK_CONTAINER (button), box);
        
    return button;
}


PGTK_WIDGET gtkAddToBox(PGTK_WIDGET box,
                            GTK_WIDGET_TYPE box_type, 
                            GTK_BOX_PACK_TYPE packing_type, 
                            PGTK_WIDGET widget,
                            GTK_WIDGET_TYPE widget_type, 
                            BOOL expand, 
                            BOOL fill, 
                            U32 padding)
{
    gprint_dbg("box=      0x%x: box_type=%d widget=0x%x widget_type=%d packing_type=%d expand=%d fill=%d padding=%d", 
                    (U32)box, box_type, (U32)widget, widget_type, packing_type, expand, fill, padding);
    _ASSERT(box);
    _ASSERT(widget);

    if ((widget_type == GTK_WIDGET_TYPE_BUTTON) || (widget_type == GTK_WIDGET_TYPE_LABEL) ||
            (widget_type == GTK_WIDGET_TYPE_HBOX) || (widget_type == GTK_WIDGET_TYPE_VBOX) ||
            (widget_type == GTK_WIDGET_TYPE_HSEPARATOR) || (widget_type == GTK_WIDGET_TYPE_VSEPARATOR) ||
            (widget_type == GTK_WIDGET_TYPE_TABLE))
    {
        switch (packing_type)
        {
            case GTK_BOX_PACK_TYPE_START:            
                gtk_box_pack_start (GTK_BOX (box), widget ,expand, fill, padding);
                break;
            case GTK_BOX_PACK_TYPE_END:            
                gtk_box_pack_end (GTK_BOX (box), widget ,expand, fill, padding);
                break;
            default:
                 gprint_wrn(" undefined packing type=%d", packing_type);
                break;
        }
    }
    else
        gprint_wrn(" undefined widget type=%d", widget_type);

    
    return box;
}

void gtkAddToTable(PGTK_WIDGET table,
                        PGTK_WIDGET widget,
                        GTK_WIDGET_TYPE widget_type, 
                        PGTK_CELL_SETTINGS settings)
{
    U32 rc = 1;
    _ASSERT(settings);    
    gprint_dbg("table=    0x%x: widget=0x%x widget_type=%d pack_type=%d left=%d right=%d top=%d bottom=%d optx=%d opty=%d padx=%d pady=%d", 
                (U32)table, (U32)widget, widget_type, settings->packing_type, settings->attach_left, settings->attach_right, 
                                settings->attach_top, settings->attach_bottom, settings->attach_option_x,
                                settings->attach_option_y, settings->padding_x, settings->padding_y);
    _ASSERT(table);
    _ASSERT(widget);    
    
    if ((widget_type == GTK_WIDGET_TYPE_BUTTON) || (widget_type == GTK_WIDGET_TYPE_LABEL))
    {
        switch (settings->packing_type)
        {
            case GTK_TABLE_PACKING_TYPE_DEFAULT:            
                gtk_table_attach_defaults (GTK_TABLE(table), widget, settings->attach_left, 
                            settings->attach_right, settings->attach_top, settings->attach_bottom);
                break;
            case GTK_TABLE_PACKING_TYPE_EXTENDED:            
                gtk_table_attach (GTK_TABLE(table), widget, settings->attach_left, settings->attach_right, 
                                settings->attach_top, settings->attach_bottom, settings->attach_option_x,
                                settings->attach_option_y, settings->padding_x, settings->padding_y);
                break;
            default:
                rc = 0;
                gprint_wrn(" undefined packing type=%d", settings->packing_type);
                break;
        }
        if (rc)
        {
            if (settings->spacing_row)
                gtk_table_set_row_spacing(GTK_TABLE(table), settings->attach_right, settings->spacing_row);
            if (settings->spacing_column)
                gtk_table_set_col_spacing(GTK_TABLE(table), settings->attach_bottom, settings->spacing_column);
        }
    }

    return;
}

/****************************************************************************************
 *           Setup widgets
 ****************************************************************************************/
void gtkSetupWindowView(PGTK_WIDGET widget, 
                            GTK_WIDGET_TYPE widget_type, 
                            PGTK_WINDOW_SETTINGS settings)
{
    _ASSERT(settings);  
    gprint_dbg("window=   0x%x: widget_type=%d type=%d PTR: D(%X) DE(%X) icon_file=<%s> title=<%s> w=%d h=%d bw=%d pos=%d", 
          (U32)widget, widget_type, settings->window_type,
          (U32)settings->ptr_destroy, (U32)settings->ptr_delete_event, settings->icon_filename, settings->title, 
          settings->width, settings->hight, settings->border_width, (U32)settings->position);
    _ASSERT(widget);

    gtk_window_set_title(GTK_WINDOW(widget), settings->title);
    gtk_window_set_default_size(GTK_WINDOW(widget), settings->width, settings->hight);
    gtk_window_set_position(GTK_WINDOW(widget), settings->position);

    if (settings->icon_filename)
    {
        gtk_window_set_icon(GTK_WINDOW(widget), gtkCreatePixbuf(settings->icon_filename));
    }

    gtk_container_set_border_width (GTK_CONTAINER (widget), settings->border_width);

    return;
}
 
void gtkConnectEventCb(PGTK_WIDGET widget, 
                            PSTR event_type, 
                            PTR cb)
{
    gprint_dbg("widget=   0x%x: event_type=%s cb=0x%x", (U32)widget, event_type, (U32)cb);
    _ASSERT(widget);
    _ASSERT(cb);

    g_signal_connect (G_OBJECT (widget), event_type, G_CALLBACK(cb), NULL);
    
    return;
}



void gtkInitWidgetSettings(PTR settings, 
                            GTK_WIDGET_TYPE widget_type)
{
    gprint_dbg("settings= 0x%x: widget_type=%d", (U32)settings, widget_type);
    _ASSERT(settings);  
    
    switch (widget_type)
    {
        case GTK_WIDGET_TYPE_WINDOW:
            {
                PGTK_WINDOW_SETTINGS s = (PGTK_WINDOW_SETTINGS)settings;
                
                s->window_type     = GTK_WINDOW_TOPLEVEL;
                s->position        = GTK_WIN_POS_NONE;
                s->border_width    = 5;
                s->width           = 200;
                s->hight           = 200;
                s->title           = "GKT Application";
                s->icon_filename   = "";
                s->ptr_delete_event= NULL;
                s->ptr_destroy     = NULL;
            }
            break;
        case GTK_WIDGET_TYPE_BUTTON:  
            {
                PGTK_BUTTON_SETTINGS s = (PGTK_BUTTON_SETTINGS)settings;

                s->button_type      = GTK_BUTTON_TYPE_LABEL;
                s->caption          = "";
                s->icon_file        = "";                
                s->exit_on_type     = GTK_BUTTON_STATE_TYPE_NONE;
                s->ptr_activate     = NULL;
                s->ptr_clicked      = NULL;
                s->ptr_enter        = NULL;
                s->ptr_leave        = NULL;
                s->ptr_pressed      = NULL;
                s->ptr_released     = NULL;
                s->width            = 40;
                s->hight            = 20; 
                s->pos_x            = 20;
                s->pos_y            = 20;     
            }
            break;
        case GTK_WIDGET_TYPE_FRAME:    
            {
                PGTK_FRAME_SETTINGS s = (PGTK_FRAME_SETTINGS)settings;
                
                s->caption          = "";
            }
            break;
        case GTK_WIDGET_TYPE_LABEL:
            {
                PGTK_LABEL_SETTINGS s = (PGTK_LABEL_SETTINGS)settings;
                
                s->caption          = "";
                s->pos_x            = 20;
                s->pos_y            = 20;       
                s->aling_x          = 0;
                s->aling_y          = 0;
            }
            break;
        case GTK_WIDGET_TYPE_VBOX:
            {
                PGTK_BOX_SETTINGS s = (PGTK_BOX_SETTINGS)settings;
                
                s->caption          = "";
                s->box_type         = GTK_WIDGET_TYPE_VBOX;
                s->same_size        = FALSE;
                s->spacing          = FALSE;                
            }
            break;
        case GTK_WIDGET_TYPE_HBOX:            
            {
                PGTK_BOX_SETTINGS s = (PGTK_BOX_SETTINGS)settings;
                
                s->caption          = "";
                s->box_type         = GTK_WIDGET_TYPE_HBOX;
                s->same_size        = FALSE;
                s->spacing          = FALSE;                
            }
            break;
        case GTK_WIDGET_TYPE_HSEPARATOR:            
            {
                PGTK_SEPARATOR_SETTINGS s = (PGTK_SEPARATOR_SETTINGS)settings;
                
                s->sepatator_type   = GTK_WIDGET_TYPE_HSEPARATOR;
                s->width            = 0;
                s->hight            = 0; 
            }
            break;            
        case GTK_WIDGET_TYPE_VSEPARATOR:            
            {
                PGTK_SEPARATOR_SETTINGS s = (PGTK_SEPARATOR_SETTINGS)settings;
                
                s->sepatator_type   = GTK_WIDGET_TYPE_VSEPARATOR;
                s->width            = 0;
                s->hight            = 0; 
            }
            break;            
        case GTK_WIDGET_TYPE_TABLE:            
            {
                PGTK_TABLE_SETTINGS s = (PGTK_TABLE_SETTINGS)settings;
                
                s->same_size        = FALSE;
                s->rows             = 2;
                s->columns          = 2; 
                s->spacing_rows     = 2;
                s->spacing_columns  = 2;                
            }
            break;            
        case GTK_WIDGET_TYPE_CELL:            
            {
                PGTK_CELL_SETTINGS s = (PGTK_CELL_SETTINGS)settings;

                s->packing_type     = GTK_TABLE_PACKING_TYPE_EXTENDED;
                s->attach_left      = 0;
                s->attach_right     = 1;
                s->attach_top       = 0;
                s->attach_bottom    = 1;                
                s->attach_option_x  = GTK_SHRINK | GTK_FILL;
                s->attach_option_y  = GTK_SHRINK | GTK_FILL;
                s->padding_x        = 1;                
                s->padding_y        = 1;                
                s->spacing_row      = 0;                
                s->spacing_column   = 0;                
            }
            break;            

        default:
             gprint_wrn(" undefined type widget_type=%d", widget_type);
            break;
    }
    
    return;
}



/****************************************************************************************
 *           Additional set
 ****************************************************************************************/
PGTK_PIXBUF gtkCreatePixbuf(const PSTR filename)
{
    PGTK_PIXBUF     pixbuf;
    PGTK_ERROR      error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    gprint_dbg("pixbuf=   0x%x: filename=%s", (U32)pixbuf, filename);
    
    if(!pixbuf) 
    {
       fprintf(stderr, "%s\n", error->message);
       g_error_free(error);
    }

    return (PGTK_PIXBUF)pixbuf;
}




/****************************************************************************************
 *          Data  set
 ****************************************************************************************/
 
 void gtkSetText( PGTK_WIDGET widget, 
                    GTK_WIDGET_TYPE widget_type, 
                    PSTR text)
 {
    gprint_dbg("widget=0x%x: widget_type=%d text=<%s>", (U32)widget, widget_type, text);
    _ASSERT(widget);
    
    switch (widget_type)
    {
        case GTK_WIDGET_TYPE_WINDOW:
        case GTK_WIDGET_TYPE_BUTTON:            
        case GTK_WIDGET_TYPE_FRAME:            
            gprint_wrn(" undefined type widget_type=%d", widget_type);
            break;
        case GTK_WIDGET_TYPE_LABEL:
            gtk_label_set_text(GTK_LABEL(widget), text);
            break;
        default:
             gprint_wrn(" undefined type widget_type=%d", widget_type);
    
            break;
    }
    
     return;
 }

 void gtkSetNum( PGTK_WIDGET widget, 
                    GTK_WIDGET_TYPE widget_type, 
                    U32 number, 
                    NUM_TYPE number_type, 
                    PSTR mask)
 {
    char buf[255];
    gprint_dbg("widget=0x%x: widget_type=%d number=<%s> number_type=%d mask=<%s>", (U32)widget, widget_type, number, number_type, mask);
    _ASSERT(widget);

    switch (number_type)
    {
        case NUM_TYPE_DEC:
            sprintf(buf, "%d", number);    
            break;  
        case NUM_TYPE_HEX_L:            
            sprintf(buf, "0x%x", number);    
            break;  
        case NUM_TYPE_HEX_H:            
            sprintf(buf, "0x%X", number);    
            break;  
        case NUM_TYPE_MASK:   
            if (mask != "")
                sprintf(buf, mask, number);    
            else
                sprintf(buf, "%d", number);                    
            break;  
        default:
            sprintf(buf, "%d", number);    
            break;
    }
    
    switch (widget_type)
    {
        case GTK_WIDGET_TYPE_WINDOW:
        case GTK_WIDGET_TYPE_BUTTON:            
        case GTK_WIDGET_TYPE_FRAME:            
            gprint_wrn(" undefined type widget_type=%d", widget_type);
            break;
        case GTK_WIDGET_TYPE_LABEL:
            gtk_label_set_text(GTK_LABEL(widget), buf);
            break;
        default:
             gprint_wrn(" undefined type widget_type=%d", widget_type);
    
            break;
    }
    
     return;
 }

