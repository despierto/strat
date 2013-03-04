/*****************************************************************************
 *          
 *          START EDITOR:  print functions & definitions 
 *
 *****************************************************************************/
#include "gtk_iface.h"

void gtkInit(S32 argc, PSTR argv[])
{
    gprint_dbg("argc=%d argv=%s", (U32)argc, argv);
    gtk_init(&argc, &argv);
    
    return;
}

PGTK_WIDGET gtkNewWindow(PTR del_event, PSTR del_event_caption, PTR destroy, PSTR destroy_caption, U32 type)
{
    PGTK_WIDGET widget = gtk_window_new(type);
    gprint_dbg("widget=0x%x type=%d", (U32)widget, type);

    g_signal_connect (GTK_OBJ (widget), del_event_caption, GTK_CB(del_event), NULL);
    g_signal_connect (GTK_OBJ (widget), destroy_caption, GTK_CB(destroy), NULL);

    return widget;
}

void gtkShowWindow(PGTK_WIDGET widget)
{
    gprint_dbg("widget=0x%x", (U32)widget);
    gtk_widget_show(widget);

    return;
}

void gtkSetupWindowView(PGTK_WIDGET widget, U32 border_width)
{
    gprint_dbg("widget=0x%x border_width=%d", (U32)widget, border_width);
    gtk_container_set_border_width (GTK_CTR (widget), border_width);

    return;
}

void gtkStartApplication(void)
{
    gprint_log("start GUI");    
    gtk_main();
    gprint_log("stop GUI");    
    
    return;
}

PGTK_WIDGET gtkAddButton(PGTK_WIDGET widget, PTR ptr, PSTR caption, PSTR type, U32 exit)
{
    PGTK_WIDGET button;
    
    button = gtk_button_new_with_label(caption);

    gprint_dbg("widget=0x%x button=0x%x ptr=0x%x caption=<%s> type=<%s>", (U32)widget, (U32)button, (U32)ptr, caption, type);
    

    if (exit)
    {
        g_signal_connect_swapped (GTK_OBJ (button), type, GTK_CB(gtk_widget_destroy), GTK_OBJ (widget));
    }
    else
    {
        g_signal_connect (GTK_OBJ (button), type, GTK_CB(ptr), NULL);
    }
    
    gtk_container_add (GTK_CTR (widget), button);
    gtk_widget_show (button);
   
    return (PGTK_WIDGET)button;
}


