/*****************************************************************************
 *          
 *          START EDITOR:   application entry
 *          Authors:              - Alex Winter,  <eterno.despierto@gmail.com>
 *                                    -
 *
 *          Date:                  02.2013
 *          Version:              1.0.0.1
 *
 *****************************************************************************/
 
#include "global.h"
#include "gtk_iface.h"

void plus(PGTK_WIDGET widget, GPTR data)
{
    gprint_dbg("widget=0x%x data=0x%x", (U32)widget, (U32)data);
    return;
}
void minus(PGTK_WIDGET widget, GPTR data)
{
    gprint_dbg("widget=0x%x data=0x%x", (U32)widget, (U32)data);
    return;
}


gint delete_event(PGTK_WIDGET widget, PGTK_EVENT event, GPTR data )
{
    gprint_dbg("widget=0x%x event=0x%x data=0x%x", (U32)widget, (U32)event, (U32)data);
    
    gprint_log("call quit application");    
    gtk_main_quit ();
    return TRUE;
}

void destroy(PGTK_WIDGET widget, GPTR data)
{
    gprint_dbg("widget=0x%x data=0x%x", (U32)widget, (U32)data);

    gprint_log("call quit application.");    
    gtk_main_quit ();
    return;
}

S32 main(S32 argc, PSTR argv[])
{
    PGTK_WIDGET window;
    PGTK_WIDGET button1, button2;
    PGTK_WIDGET frame;  
    PGTK_WIDGET label;    
    PGTK_WIDGET box;
    GTK_WINDOW_SETTINGS window_settings;
    GTK_BUTTON_SETTINGS button_setting1, button_setting2;
    GTK_FRAME_SETTINGS  frame_settings;
    GTK_LABEL_SETTINGS  label_settings;
    GTK_BOX_SETTINGS    box_settings;

    gtkInitWidgetSettings((PTR)&window_settings, GTK_WIDGET_TYPE_WINDOW);
    gtkInitWidgetSettings((PTR)&button_setting1, GTK_WIDGET_TYPE_BUTTON);
    gtkInitWidgetSettings((PTR)&button_setting2, GTK_WIDGET_TYPE_BUTTON);
    gtkInitWidgetSettings((PTR)&frame_settings, GTK_WIDGET_TYPE_FRAME);    
    gtkInitWidgetSettings((PTR)&label_settings, GTK_WIDGET_TYPE_LABEL);    
    gtkInitWidgetSettings((PTR)&box_settings, GTK_WIDGET_TYPE_BOX);    

    gprint_log("entry application");    
    gtkInit(argc, argv);

    window_settings.width           = 250;
    window_settings.hight           = 180;
    window_settings.title           = " Strat Editor";
    window_settings.icon_filename   = GBL_ICON_FILE;
    window_settings.ptr_delete_event= (PTR)&delete_event;
    window_settings.ptr_destroy     = (PTR)&destroy;
    window = gtkNewWindow((PGTK_WINDOW_SETTINGS)&window_settings);

#if 0
    frame_settings.caption            = "Good day";
    frame = gtkNewFrame(window, GTK_WIDGET_TYPE_WINDOW, (PGTK_FRAME_SETTINGS)&frame_settings);

    label_settings.caption          = "label";
    label_settings.pos_x            = 190;
    label_settings.pos_y            = 58;    
    label = gtkNewLabel(frame, GTK_WIDGET_TYPE_FRAME, (PGTK_LABEL_SETTINGS)&label_settings);
#else
    box = gtkNewBox(window, GTK_WIDGET_TYPE_WINDOW, (PGTK_BOX_SETTINGS)&box_settings);
#endif

    button_setting1.caption          = "plus";
    button_setting1.ptr_clicked      = (PTR)&plus;
    button_setting1.width            = 80;
    button_setting1.hight            = 35; 
    button_setting1.pos_x            = 50;
    button_setting1.pos_y            = 20;     
    button1 = gtkNewButton(box, GTK_WIDGET_TYPE_BOX, (PGTK_BUTTON_SETTINGS)&button_setting1);

    button_setting2.caption          = "minus";
    button_setting2.ptr_clicked      = (PTR)&minus;
    button_setting2.width            = 80;
    button_setting2.hight            = 35; 
    button_setting2.pos_x            = 50;
    button_setting2.pos_y            = 80;      
    button2 = gtkNewButton(box, GTK_WIDGET_TYPE_BOX, (PGTK_BUTTON_SETTINGS)&button_setting2);
  
    //gtkShowWindow(window);
    gtkShowAllInWindow(window);

    gtkStartApplication();
    
    gprint_log("quit application");    
    return 0;
}
