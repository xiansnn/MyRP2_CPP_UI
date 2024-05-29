#include "test_manager.h"

Test_Manager::Test_Manager()
    : UIObjectManager()
{
    make_manager_active();
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
    // case ControlEvent::PUSH:
    //     // printf("manager_PUSH\n");
    //     break;
    // case ControlEvent::DOUBLE_PUSH:
    //     // printf("manager_DOUBLE_PUSH\n");
    //     break;
    case ControlEvent::LONG_PUSH:
        // printf("manager_LONG_PUSH\n");
        if (current_active_model != this)
            current_active_model->process_control_event(_event);
        break;
    // case ControlEvent::RELEASED_AFTER_LONG_TIME:
    //     // printf("manager_RELEASED_AFTER_LONG_TIME\n");
    //     break;
    case ControlEvent::RELEASED_AFTER_SHORT_TIME:
        // printf("manager_RELEASED_AFTER_SHORT_TIME\n");
        if (current_active_model == this)
            make_managed_object_active();
        else
            make_manager_active();
        break;
    case ControlEvent::INCREMENT:
        // printf("manager_INCREMENT\n");
        if (current_active_model == this)
            increment_focus();
        else
            current_active_model->process_control_event(_event);
        break;
    case ControlEvent::DECREMENT:
        // printf("manager_DECREMENT\n");
        if (current_active_model == this)
            decrement_focus();
        else
            current_active_model->process_control_event(_event);
        break;
    // case ControlEvent::TIME_OUT:
    //     // printf("manager_TIME_OUT\n");
    //     break;

    default:
        break;
    }
}
