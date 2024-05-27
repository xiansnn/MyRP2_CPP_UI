#if !defined(WIDGET_PRINT_SERIAL_MONITOR_H)
#define WIDGET_PRINT_SERIAL_MONITOR_H

#include <string>
#include "controlled_value.h"

#include "ui_core.h"

class WTextSerialMonitor : public UIWidget
{
private:
    ControlledValue *actual_displayed_object;
    void draw();

public:
    WTextSerialMonitor();
    ~WTextSerialMonitor();
    void refresh();
    void set_displayed_object(ControlledValue *_actual_displayed_object);
};

class WCursorOnSerialMonitor : public UIWidget
{
private:
    float slope;
    float offset;
    uint8_t max_line_width = 21;

    ControlledValue *actual_displayed_object;
    void draw();

public:
    WCursorOnSerialMonitor(/* args */);
    ~WCursorOnSerialMonitor();
    void refresh();
    void set_displayed_object(ControlledValue *_actual_displayed_object);
};

#endif // WIDGET_PRINT_SERIAL_MONITOR_H
