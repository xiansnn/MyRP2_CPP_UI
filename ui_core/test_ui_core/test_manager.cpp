/**
 * @file test_manager.cpp
 * @author xiansnn (xiansnn@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "test_manager.h"

Test_Manager::Test_Manager(UIController * _controller)
    : UIObjectManager()
{
    make_manager_active();
    update_current_controller(_controller);
}

Test_Manager::~Test_Manager()
{
}

void Test_Manager::process_control_event(ControlEvent _event)
{
    switch (_event)
    {
    case ControlEvent::NOOP:
        /* code */
        break;
    case ControlEvent::LONG_PUSH:
        if (current_active_model != this)
            current_active_model->process_control_event(_event);
        break;
    case ControlEvent::RELEASED_AFTER_SHORT_TIME:
        if (current_active_model == this)
            make_managed_object_active();
        else
            make_manager_active();
        break;
    case ControlEvent::INCREMENT:
        if (current_active_model == this)
            increment_focus();
        else
            current_active_model->process_control_event(_event);
        break;
    case ControlEvent::DECREMENT:
        if (current_active_model == this)
            decrement_focus();
        else
            current_active_model->process_control_event(_event);
        break;
    default:
        break;
    }
}