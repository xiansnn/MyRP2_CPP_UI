#if !defined(WIDGET_PRINT_SERIAL_MONITOR_H)
#define WIDGET_PRINT_SERIAL_MONITOR_H

#include <string>
#include "t_controlled_value.h"
#include "t_manager.h"

#include "ui_core.h"

/**
 * @brief This is an implementation of a pseudo-widget for test_ui_core program.
 * 
 * It write status and value of Test_IncrementalValue on the serial monitor
 * 
 */
class Test_CursorWidgetWithIncrementalValue : public UIWidget
{
private:
    float char_position_slope;
    float char_position_offset;
    uint8_t max_line_width = 21;
    int value_to_char_position();

    Test_IncrementalValue *actual_displayed_object;
    void draw();

public:
    /**
     * @brief Construct a new Test Cursor Widget With Incremental Value object
     * 
     * @param _actual_displayed_object 
     */
    Test_CursorWidgetWithIncrementalValue(Test_IncrementalValue *_actual_displayed_object);
    /**
     * @brief Destroy the Test Cursor Widget With Incremental Value object
     * 
     */
    ~Test_CursorWidgetWithIncrementalValue();
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
