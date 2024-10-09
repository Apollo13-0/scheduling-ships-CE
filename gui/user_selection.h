#ifndef USER_SELECTION_H
#define USER_SELECTION_H

#include <gtk/gtk.h>

typedef struct {
    const gchar *selected_calendarization;
    const gchar *extra_param_text;
    const gchar *selected_channel;
} UserSelection;

#endif // USER_SELECTION_H