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
    gtk_widget_show(widget);

    return;
}

void gtkShowAllInWindow(PGTK_WIDGET widget)
{
    gprint_dbg("widget=   0x%x:", (U32)widget);
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
    PGTK_WIDGET     widget = gtk_window_new(settings->window_type);

    gprint_dbg("window=   0x%x: title=<%s> w=%d h=%d bw=%d pos=%d", 
        (U32)widget, settings->title, settings->width, settings->hight, settings->border_width, (U32)settings->position);
    gprint_dbg("window=   0x%x: type=%d PTR: D(%X) DE(%X) icon_file=<%s>", 
            (U32)widget, settings->window_type, (U32)settings->ptr_destroy, (U32)settings->ptr_delete_event, settings->icon_filename);

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

PGTK_WIDGET gtkNewFrame(PGTK_WIDGET widget, GTK_WIDGET_TYPE widget_type, PGTK_FRAME_SETTINGS settings)
{
    PGTK_WIDGET     frame = gtk_fixed_new();
    gprint_dbg("frame=    0x%x: widget=0x%x widget_type=%d caption=<%s>", (U32)frame, (U32)widget, widget_type, settings->caption);

    gtk_container_add (GTK_CONTAINER (widget), frame);
    
    return frame;
}

PGTK_WIDGET gtkNewBox(PGTK_WIDGET widget, GTK_WIDGET_TYPE widget_type, PGTK_BOX_SETTINGS settings)
{
    PGTK_WIDGET     box = gtk_hbox_new (FALSE, 0);
    gprint_dbg("box=      0x%x: widget=0x%x widget_type=%d", (U32)box, (U32)widget, widget_type);

    gtk_container_add (GTK_CONTAINER (widget), box);
    
    return box;
}

PGTK_WIDGET gtkNewLabel(PGTK_WIDGET widget, GTK_WIDGET_TYPE widget_type, PGTK_LABEL_SETTINGS settings)
{
    PGTK_WIDGET     label = gtk_label_new(settings->caption);
    gprint_dbg("label=    0x%x: widget=0x%x widget_type=%d caption=<%s> x=%d y=%d", 
        (U32)label, (U32)widget, widget_type, settings->caption,  settings->pos_x, settings->pos_y);

    if (widget_type == GTK_WIDGET_TYPE_FRAME)
        gtk_fixed_put(GTK_FIXED(widget), label, settings->pos_x, settings->pos_y);
    
    return label;
}

PGTK_WIDGET gtkNewButton(PGTK_WIDGET widget, GTK_WIDGET_TYPE widget_type, PGTK_BUTTON_SETTINGS settings)
{
    PGTK_WIDGET     button;

    button = gtk_button_new_with_label(settings->caption);
    gprint_dbg("button=   0x%x: widget=0x%x widget_type=%d caption=<%s> w=%d h=%d x=%d y=%d", 
        (U32)button, (U32)widget, widget_type, settings->caption, settings->width, settings->hight, settings->pos_x, settings->pos_y);
    gprint_dbg("button=   0x%x: exit_type=<%s> PTR: A(%X) C(%X) E(%X) L(%X) P(%X) R(%X)", 
        (U32)button, settings->exit_on_type,
        (U32)settings->ptr_activate, (U32)settings->ptr_clicked, (U32)settings->ptr_enter, 
        (U32)settings->ptr_leave, (U32)settings->ptr_pressed, (U32)settings->ptr_released);

    if (settings->ptr_activate)
        gtkConnectEventCb(button, GTK_BUTTON_TYPE_ACTIVE, settings->ptr_activate);
    if (settings->ptr_clicked)
        gtkConnectEventCb(button, GTK_BUTTON_TYPE_CLICKED, settings->ptr_clicked);
    if (settings->ptr_enter)
        gtkConnectEventCb(button, GTK_BUTTON_TYPE_ENTER, settings->ptr_enter);
    if (settings->ptr_leave)
        gtkConnectEventCb(button, GTK_BUTTON_TYPE_LEAVE, settings->ptr_leave);
    if (settings->ptr_pressed)
        gtkConnectEventCb(button, GTK_BUTTON_TYPE_PRESSED, settings->ptr_pressed);
    if (settings->ptr_released)
        gtkConnectEventCb(button, GTK_BUTTON_TYPE_RELEASED, settings->ptr_released);

    if (settings->exit_on_type)
        g_signal_connect_swapped (G_OBJECT (button), settings->exit_on_type, G_CALLBACK(gtk_widget_destroy), G_OBJECT (widget));

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
    else if (widget_type == GTK_WIDGET_TYPE_BOX)
    {
        gtkAddToBox(widget, button, GTK_WIDGET_TYPE_BUTTON);
    }
    
    return (PGTK_WIDGET)button;
}

PGTK_WIDGET gtkAddToBox(PGTK_WIDGET box, PGTK_WIDGET widget, GTK_WIDGET_TYPE widget_type)
{
    gprint_dbg("box=      0x%x: widget=0x%x widget_type=%d", (U32)box, (U32)widget, widget_type);

    if (widget_type == GTK_WIDGET_TYPE_BUTTON)
        gtk_box_pack_start (GTK_BOX (box), widget ,TRUE, TRUE, 0);
    
    return box;
}



/****************************************************************************************
 *           Setup widgets
 ****************************************************************************************/
void gtkSetupWindowView(PGTK_WIDGET widget, GTK_WIDGET_TYPE widget_type, PGTK_WINDOW_SETTINGS settings)
{
    gprint_dbg("window=   0x%x: widget_type=%d type=%d PTR: D(%X) DE(%X) icon_file=<%s> title=<%s> w=%d h=%d bw=%d pos=%d", 
          (U32)widget, widget_type, settings->window_type,
          (U32)settings->ptr_destroy, (U32)settings->ptr_delete_event, settings->icon_filename, settings->title, 
          settings->width, settings->hight, settings->border_width, (U32)settings->position);

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
 

void gtkConnectEventCb(PGTK_WIDGET widget, PSTR event_type, PTR cb)
{
    gprint_dbg("widget=   0x%x: event_type=%s cb=0x%x", (U32)widget, event_type, (U32)cb);
    g_signal_connect (G_OBJECT (widget), event_type, G_CALLBACK(cb), NULL);
    
    return;
}



void gtkInitWidgetSettings(PTR settings, GTK_WIDGET_TYPE widget_type)
{
    gprint_dbg("settings= 0x%x: widget_type=%d", (U32)settings, widget_type);
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
                
                s->caption          = "";
                s->exit_on_type     = GTK_BUTTON_TYPE_NONE;
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
            }
            break;

        case GTK_WIDGET_TYPE_BOX:
            {
                PGTK_BOX_SETTINGS s = (PGTK_BOX_SETTINGS)settings;
                
                s->caption          = "";
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
 
 void gtkSetText(PGTK_WIDGET widget, GTK_WIDGET_TYPE widget_type, PSTR text)
 {
    gprint_dbg("widget=0x%x: widget_type=%d text=<%s>", (U32)widget, widget_type, text);
    
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

 void gtkSetNum(PGTK_WIDGET widget, GTK_WIDGET_TYPE widget_type, U32 number, NUM_TYPE number_type, PSTR mask)
 {
    char buf[255];
    gprint_dbg("widget=0x%x: widget_type=%d number=<%s> number_type=%d mask=<%s>", (U32)widget, widget_type, number, number_type, mask);

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

