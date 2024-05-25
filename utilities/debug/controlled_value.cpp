#include "controlled_value.h"

ControlledValue::ControlledValue(int _min_value, int _max_value, bool _is_wrapable, int increment)
    : UIControlledIncrementalValue(_min_value, _max_value, _is_wrapable, increment)
{
}

ControlledValue::~ControlledValue()
{
}
