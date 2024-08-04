/**
 * @file test_controlled_value.cpp
 * @author xiansnn (xiansnn@hotmail.com)
 * @brief companion file to test_ui_core.cpp
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "test_controlled_value.h"

TestIncrementalValue::TestIncrementalValue(std::string _name, int _min_value, int _max_value, bool _is_wrappable, int increment)
    : UIControlledIncrementalValue(_min_value, _max_value, _is_wrappable, increment)
{
    this->name = _name;
}

TestIncrementalValue::~TestIncrementalValue()
{
}

/**
 * @brief The event processed by TestIncrementalValue for this test are:
 * 
 * - LONG_PUSH: set value to 0.
 * 
 * - INCREMENT:
 * 
 * - DECREMENT:
 * 
 * @param _event 
 */
void TestIncrementalValue::process_control_event(ControlEvent _event)
{
    switch (_event)
    {
    case ControlEvent::LONG_PUSH:
        this->set_clipped_value(0);
        break;
    case ControlEvent::INCREMENT:
        increment_value();
        break;
    case ControlEvent::DECREMENT:
        decrement_value();
        break;
    default:
        printf("TestIncrementalValue::process_control_event(ControlEvent _event) = default\n");
        break;
    }
}

std::string TestIncrementalValue::get_name()
{
    return name;
}
