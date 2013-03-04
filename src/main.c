/*****************************************************************************
 *          
 *          START EDITOR:  application entry
 *
 *****************************************************************************/
#include "global.h"
#include "gtk_iface.h"

void hello(PGTK_WIDGET widget, GPTR data)
{
    gprint_dbg("widget=0x%x data=0x%x", (U32)widget, (U32)data);
    return;
}

void hello1(PGTK_WIDGET widget, GPTR data)
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
    PGTK_WIDGET button;

    gprint_log("entry application");    

    gtkInit(argc, argv);

    window = gtkNewWindow((PTR)&delete_event, "delete_event", (PTR)&destroy, "destroy", GTK_WINDOW_TYPE_TOPLEVEL);
    
    gtkSetupWindowView(window, 10);
    
    button = gtkAddButton(window, (PTR)&hello, "do it (1)", GTK_BUTTON_TYPE_CLECKED, 0);
    
    gtkShowWindow(window);
    gtkStartApplication();
    
    gprint_log("quit application");    
    return 0;
}
