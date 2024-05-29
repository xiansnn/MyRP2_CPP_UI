#if !defined(WIDGET_PRINT_SERIAL_MONITOR_H)
#define WIDGET_PRINT_SERIAL_MONITOR_H

#include <string>
#include "test_controlled_value.h"
#include "test_manager.h"

#include "ui_core.h"

class TestCursorWidgetWithIncrementalValue : public UIWidget
{
private:
    float slope;
    float offset;
    uint8_t max_line_width = 21;

    TestIncrementalValue *actual_displayed_object;
    void draw();

public:
    TestCursorWidgetWithIncrementalValue();
    ~TestCursorWidgetWithIncrementalValue();
    void refresh();
    void set_displayed_object(TestIncrementalValue *_actual_displayed_object);
};

// class WCursorOnSerialMonitor : public UIWidget
// {
// private:
//     float slope;
//     float offset;
//     uint8_t max_line_width = 21;

//     TestIncrementalValue *actual_displayed_object;
//     void draw();

// public:
//     WCursorOnSerialMonitor(/* args */);
//     ~WCursorOnSerialMonitor();
//     void refresh();
//     void set_displayed_object(TestIncrementalValue *_actual_displayed_object);
// };

class TestObjectManagerWidget : public UIWidget
{
private:
    Test_Manager * actual_displayed_object;
    void draw();
public:
    TestObjectManagerWidget(/* args */);
    ~TestObjectManagerWidget();
    void set_displayed_object(Test_Manager* _manager);
    void refresh();
};

#endif // WIDGET_PRINT_SERIAL_MONITOR_H
