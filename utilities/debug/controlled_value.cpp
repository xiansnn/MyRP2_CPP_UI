#include "controlled_value.h"

ControlledValue::ControlledValue(int _min_value, int _max_value, bool _is_wrapable, int increment)
    : UIControlledIncrementalValue(_min_value, _max_value, _is_wrapable, increment)
{
}

ControlledValue::~ControlledValue()
{
}

void ControlledValue::process_control_event(ControlEvent _event)
{
    switch (_event)
    {
    case ControlEvent::NOOP:
        /* code */
        break;
    case ControlEvent::PUSH:
        printf("PUSH\n");
        break;
    case ControlEvent::DOUBLE_PUSH:
        printf("DOUBLE_PUSH\n");
        break;
    case ControlEvent::LONG_PUSH:
        printf("LONG_PUSH\n");
        break;
    case ControlEvent::RELEASED_AFTER_LONG_TIME:
        printf("RELEASED_AFTER_LONG_TIME\n");
        break;
    case ControlEvent::RELEASED_AFTER_SHORT_TIME:
        printf("RELEASED_AFTER_SHORT_TIME\n");
        break;
    case ControlEvent::INCREMENT:
        printf("INCREMENT\n");
        increment_value();
        break;
    case ControlEvent::DECREMENT:
        printf("DECREMENT\n");
        decrement_value();
        break;
    case ControlEvent::TIME_OUT:
        printf("TIME_OUT\n");
        break;

    default:
        break;
    }
}
