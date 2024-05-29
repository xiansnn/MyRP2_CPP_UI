#include "test_controlled_value.h"

TestIncrementalValue::TestIncrementalValue(std::string _name, int _min_value, int _max_value, bool _is_wrapable, int increment)
    : UIControlledIncrementalValue(_min_value, _max_value, _is_wrapable, increment)
{
    this->name = _name;
}

TestIncrementalValue::~TestIncrementalValue()
{
}

void TestIncrementalValue::process_control_event(ControlEvent _event)
{
    switch (_event)
    {
    // case ControlEvent::NOOP:
    //     /* code */
    //     break;
    // case ControlEvent::PUSH:
    //     printf("PUSH\n");
    //     break;
    // case ControlEvent::DOUBLE_PUSH:
    //     printf("DOUBLE_PUSH\n");
    //     break;
    case ControlEvent::LONG_PUSH:
        // printf("LONG_PUSH\n");
        this->set_clipped_value(0);
        break;
    // case ControlEvent::RELEASED_AFTER_LONG_TIME:
    //     printf("RELEASED_AFTER_LONG_TIME\n");
    //     break;
    // case ControlEvent::RELEASED_AFTER_SHORT_TIME:
    //     printf("RELEASED_AFTER_SHORT_TIME\n");
    //     break;
    case ControlEvent::INCREMENT:
        // printf("INCREMENT\n");
        increment_value();
        break;
    case ControlEvent::DECREMENT:
        // printf("DECREMENT\n");
        decrement_value();
        break;
    // case ControlEvent::TIME_OUT:
    //     printf("TIME_OUT\n");
    //     break;

    // case ControlEvent::DECREMENT:
    default:
        printf("TestIncrementalValue::process_control_event(ControlEvent _event) = default\n");
        break;
    }
}

std::string TestIncrementalValue::get_name()
{
    return name;
}
