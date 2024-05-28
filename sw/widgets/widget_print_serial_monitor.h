#if !defined(WIDGET_PRINT_SERIAL_MONITOR_H)
#define WIDGET_PRINT_SERIAL_MONITOR_H

#include <string>
#include "test_controlled_value.h"

#include "ui_core.h"

class WTextSerialMonitor : public UIWidget
{
private:
    Test_ControlledValue *actual_displayed_object;
    void draw();

public:
    WTextSerialMonitor();
    ~WTextSerialMonitor();
    void refresh();
    void set_displayed_object(Test_ControlledValue *_actual_displayed_object);
};

class WCursorOnSerialMonitor : public UIWidget
{
private:
    float slope;
    float offset;
    uint8_t max_line_width = 21;

    Test_ControlledValue *actual_displayed_object;
    void draw();

public:
    WCursorOnSerialMonitor(/* args */);
    ~WCursorOnSerialMonitor();
    void refresh();
    void set_displayed_object(Test_ControlledValue *_actual_displayed_object);
};

#endif // WIDGET_PRINT_SERIAL_MONITOR_H
