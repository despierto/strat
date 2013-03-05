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
    PGTK_WIDGET label, label_1;    
    PGTK_WIDGET hbox;
    PGTK_WIDGET vbox;    
    GTK_WINDOW_SETTINGS window_settings;
    GTK_BUTTON_SETTINGS button_setting1, button_setting2;
    GTK_FRAME_SETTINGS  frame_settings;
    GTK_LABEL_SETTINGS  label_settings, label_1_settings;
    GTK_BOX_SETTINGS    hbox_settings;
    GTK_BOX_SETTINGS    vbox_settings;

    gtkInitWidgetSettings((PTR)&window_settings, GTK_WIDGET_TYPE_WINDOW);
    gtkInitWidgetSettings((PTR)&button_setting1, GTK_WIDGET_TYPE_BUTTON);
    gtkInitWidgetSettings((PTR)&button_setting2, GTK_WIDGET_TYPE_BUTTON);
    gtkInitWidgetSettings((PTR)&frame_settings, GTK_WIDGET_TYPE_FRAME);    
    gtkInitWidgetSettings((PTR)&label_settings, GTK_WIDGET_TYPE_LABEL);    
    gtkInitWidgetSettings((PTR)&label_1_settings, GTK_WIDGET_TYPE_LABEL);     
    gtkInitWidgetSettings((PTR)&hbox_settings, GTK_WIDGET_TYPE_HBOX);    
    gtkInitWidgetSettings((PTR)&vbox_settings, GTK_WIDGET_TYPE_VBOX);        

    gprint_log("entry application");    
    gtkInit(argc, argv);

    window_settings.width           = 1250;
    window_settings.hight           = 600;
    window_settings.title           = " Strat Editor";
    window_settings.icon_filename   = GBL_ICON_FILE;
    window_settings.ptr_delete_event= (PTR)&delete_event;
    window_settings.ptr_destroy     = (PTR)&destroy;
    window = gtkNewWindow((PGTK_WINDOW_SETTINGS)&window_settings);

#if 0
    frame_settings.caption            = "Good day";
    frame = gtkNewFrame(window, GTK_WIDGET_TYPE_WINDOW, (PGTK_FRAME_SETTINGS)&frame_settings);
#else
 
    vbox_settings.box_type          = GTK_WIDGET_TYPE_VBOX;
    vbox_settings.set_same_length   = FALSE;
    vbox_settings.spacing           = 0;
    vbox = gtkNewBox(window, GTK_WIDGET_TYPE_WINDOW, (PGTK_BOX_SETTINGS)&vbox_settings);

    hbox_settings.box_type          = GTK_WIDGET_TYPE_HBOX;
    hbox_settings.set_same_length   = TRUE;;
    hbox_settings.spacing           = 0;
    hbox = gtkNewBox(vbox, GTK_WIDGET_TYPE_VBOX, (PGTK_BOX_SETTINGS)&hbox_settings);

#endif

    //gtkAddToBox(vbox, GTK_WIDGET_TYPE_VBOX, GTK_BOX_PACK_TYPE_START, hbox, GTK_WIDGET_TYPE_HBOX, FALSE, FALSE, 0);

    label_1_settings.caption          = "gtk_hbox_new (FALSE, 0)";
    label_1_settings.aling_y          = 0.5;
    label_1_settings.aling_x          = 0.5;

    //label_1 = gtkNewLabel(vbox, GTK_WIDGET_TYPE_VBOX, (PGTK_LABEL_SETTINGS)&label_1_settings);
    label_1 = gtkNewLabel(NULL, GTK_WIDGET_TYPE_NONE, (PGTK_LABEL_SETTINGS)&label_1_settings);
    gtkAddToBox(vbox, GTK_WIDGET_TYPE_VBOX, GTK_BOX_PACK_TYPE_END, label_1, GTK_WIDGET_TYPE_LABEL, FALSE, FALSE, 0);
 


    button_setting1.caption          = "plus";
    button_setting1.ptr_clicked      = (PTR)&plus;
    button_setting1.width            = 180;
    button_setting1.hight            = 35; 
    button_setting1.pos_x            = 70;
    button_setting1.pos_y            = 20;     
    button1 = gtkNewButton(NULL, GTK_WIDGET_TYPE_NONE, (PGTK_BUTTON_SETTINGS)&button_setting1);
    gtkAddToBox(hbox, GTK_WIDGET_TYPE_HBOX, GTK_BOX_PACK_TYPE_START, button1, GTK_WIDGET_TYPE_BUTTON, FALSE, FALSE, 0);

    button_setting2.caption          = "minus";
    button_setting2.ptr_clicked      = (PTR)&minus;
    button_setting2.width            = 80;
    button_setting2.hight            = 135; 
    button_setting2.pos_x            = 50;
    button_setting2.pos_y            = 80;      
    button2 = gtkNewButton(NULL, GTK_WIDGET_TYPE_NONE, (PGTK_BUTTON_SETTINGS)&button_setting2);
    
    gtkAddToBox(hbox, GTK_WIDGET_TYPE_HBOX, GTK_BOX_PACK_TYPE_START, button2, GTK_WIDGET_TYPE_BUTTON, FALSE, FALSE, 0);

    label_settings.caption          = "label";
    label_settings.pos_x            = 190;
    label_settings.pos_y            = 58;    
    label_settings.aling_y          = 1;
    label_settings.aling_x          = 0.5;    
    label = gtkNewLabel(NULL, GTK_WIDGET_TYPE_NONE, (PGTK_LABEL_SETTINGS)&label_settings);
    gtkAddToBox(hbox, GTK_WIDGET_TYPE_HBOX, GTK_BOX_PACK_TYPE_END, label, GTK_WIDGET_TYPE_LABEL, FALSE, FALSE, 0);
    
    //gtkShowWindow(window);
    gtkShowAllInWindow(window);

    gtkStartApplication();
    
    gprint_log("quit application");    
    return 0;
}
