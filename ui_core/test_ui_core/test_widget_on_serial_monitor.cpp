/**
 * @file test_widget_on_serial_monitor.cpp
 * @author xiansnn (xiansnn@hotmail.com)
 * @brief This is the companion file of test_ui_core program
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "test_widget_on_serial_monitor.h"
#include <sstream>

std::map<ControlledObjectStatus, std::string> status_to_string{
    {ControlledObjectStatus::IS_WAITING, "IS_WAITING"},
    {ControlledObjectStatus::HAS_FOCUS, "HAS_FOCUS"},
    {ControlledObjectStatus::IS_ACTIVE, "IS_ACTIVE"}};

TestCursorWidgetWithIncrementalValue::TestCursorWidgetWithIncrementalValue(TestIncrementalValue *_actual_displayed_object)
    : UIWidget(nullptr, 128, 8, 0, 0, false)
{
    this->set_displayed_model(_actual_displayed_object);
    this->actual_displayed_object = _actual_displayed_object;

    char_position_slope = (max_line_width - 1.) / (actual_displayed_object->get_max_value() - actual_displayed_object->get_min_value());
    char_position_offset = 1 - char_position_slope * actual_displayed_object->get_min_value();
}

TestCursorWidgetWithIncrementalValue::~TestCursorWidgetWithIncrementalValue()
{
}

void TestCursorWidgetWithIncrementalValue::refresh()
{
    if (this->actual_displayed_object->has_changed())
    {
        draw();
        this->actual_displayed_object->clear_change_flag();
    }
}

int TestCursorWidgetWithIncrementalValue::value_to_char_position()
{
    return (char_position_slope * actual_displayed_object->get_value() + char_position_offset);
}

void TestCursorWidgetWithIncrementalValue::draw()
{
    switch (actual_displayed_object->get_status())
    {
    case ControlledObjectStatus::IS_WAITING:
        printf("[%s] %s with value=%d\n",
               actual_displayed_object->get_name().c_str(), status_to_string[actual_displayed_object->get_status()].c_str(), actual_displayed_object->get_value());
        break;
    case ControlledObjectStatus::HAS_FOCUS:
        printf("[%s] %s with value=%d\n",
               actual_displayed_object->get_name().c_str(), status_to_string[actual_displayed_object->get_status()].c_str(), actual_displayed_object->get_value());
        break;
    case ControlledObjectStatus::IS_ACTIVE:
        printf("[%s] %s with value= %d %*c\n",
               actual_displayed_object->get_name().c_str(), status_to_string[actual_displayed_object->get_status()].c_str(), actual_displayed_object->get_value(), value_to_char_position(), '|');
        break;
    default:
        break;
    }
}

void TestObjectManagerWidget::draw()
{
    std::string text = "manager " + status_to_string[actual_displayed_object->get_status()] + " with value=" + std::to_string(actual_displayed_object->get_value()) + "\n";
    printf(text.c_str());
}

TestObjectManagerWidget::TestObjectManagerWidget(Test_Manager *_manager)
    : UIWidget(nullptr, 128, 8, 0, 0, false)
{
    this->set_displayed_model(_manager);
    this->actual_displayed_object = _manager;
}

TestObjectManagerWidget::~TestObjectManagerWidget()
{
}

void TestObjectManagerWidget::refresh()
{
    if (this->actual_displayed_object->has_changed())
    {
        draw();
        this->actual_displayed_object->clear_change_flag();
    }
}

void TestSetOfWidget::draw()
{
}

TestSetOfWidget::TestSetOfWidget()
    : UIWidget(nullptr, 128, 8, 0, 0, false)
{
}

TestSetOfWidget::~TestSetOfWidget()
{
}
