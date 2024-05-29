#if !defined(WIDGET_PRINT_SERIAL_MONITOR_H)
#define WIDGET_PRINT_SERIAL_MONITOR_H

#include <string>
#include "test_controlled_value.h"
#include "test_manager.h"

#include "ui_core.h"

class TestCursorWidgetWithIncrementalValue : public UIWidget
{
private:
    float char_position_slope;
    float char_position_offset;
    uint8_t max_line_width = 21;
    int value_to_char_position();

    TestIncrementalValue *actual_displayed_object;
    void draw();

public:
    TestCursorWidgetWithIncrementalValue(TestIncrementalValue *_actual_displayed_object);
    ~TestCursorWidgetWithIncrementalValue();
    void refresh();
};

class TestObjectManagerWidget : public UIWidget
{
private:
    Test_Manager * actual_displayed_object;
    void draw();
public:
    TestObjectManagerWidget(Test_Manager* _manager);
    ~TestObjectManagerWidget();
    void refresh();
};

#endif // WIDGET_PRINT_SERIAL_MONITOR_H
