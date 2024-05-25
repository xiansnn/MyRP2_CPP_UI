#if !defined(CONTROLLED_VALUE_H)
#define CONTROLLED_VALUE_H

#include "ui_core.h"

class ControlledValue : UIControlledIncrementalValue
{
private:
    /* data */
public:
    ControlledValue(int _min_value = 0, int _max_value = 10, bool _is_wrapable = false, int increment = 1);
    ~ControlledValue();
};


#endif // CONTROLLED_VALUE_H
