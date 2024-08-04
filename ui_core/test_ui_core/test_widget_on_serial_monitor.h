#if !defined(WIDGET_PRINT_SERIAL_MONITOR_H)
#define WIDGET_PRINT_SERIAL_MONITOR_H

#include <string>
#include "test_controlled_value.h"
#include "test_manager.h"

#include "ui_core.h"

/**
 * @brief This is an implementation of a pseudo-widget for test_ui_core program.
 * 
 * It write status and value of TestIncrementalValue on the serial monitor
 * 
 */
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
    /**
     * @brief Construct a new Test Cursor Widget With Incremental Value object
     * 
     * @param _actual_displayed_object 
     */
    TestCursorWidgetWithIncrementalValue(TestIncrementalValue *_actual_displayed_object);
    /**
     * @brief Destroy the Test Cursor Widget With Incremental Value object
     * 
     */
    ~TestCursorWidgetWithIncrementalValue();
    /**
     * @brief Implement a refresh function adapted to the current test program with the private function draw()
     * 
     */
    void refresh();
};

/**
 * @brief This is an implementation of a pseudo-widget for test_ui_core program.
 * 
 * It write status and value of Test_Manager on the serial monitor
 *
 */
class TestObjectManagerWidget : public UIWidget
{
private:
    Test_Manager * actual_displayed_object;
    void draw();
public:
    /**
     * @brief Construct a new Test Object Manager Widget object
     * 
     * @param _manager 
     */
    TestObjectManagerWidget(Test_Manager* _manager);
    /**
     * @brief Destroy the Test Object Manager Widget object
     * 
     */
    ~TestObjectManagerWidget();
    /**
     * @brief Implement a refresh function adapted to the current test program with the private function draw()
     * 
     */
    void refresh();
};

/**
 * @brief test the composite widget features
 * 
 */
class TestSetOfWidget : public UIWidget
{
private:
    /* data */
    void draw();
public:
    /**
     * @brief 
     * 
     */
    TestSetOfWidget(/* args */);
    /**
     * @brief Destroy the Test Set Of Widget object
     * 
     */
    ~TestSetOfWidget();
};



#endif // WIDGET_PRINT_SERIAL_MONITOR_H
