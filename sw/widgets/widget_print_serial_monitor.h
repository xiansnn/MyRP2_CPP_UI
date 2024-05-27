#if !defined(WIDGET_PRINT_SERIAL_MONITOR_H)
#define WIDGET_PRINT_SERIAL_MONITOR_H

#include <string>
#include "controlled_value.h"

#include "ui_core.h"

class WTextSerialMonitor : public UIWidget
{
private:
    ControlledValue * actual_displayed_object;
    void draw();
public:
    WTextSerialMonitor();
    ~WTextSerialMonitor();
    void refresh();
    void set_displayed_object(ControlledValue * _actual_displayed_object);
};



#endif // WIDGET_PRINT_SERIAL_MONITOR_H
