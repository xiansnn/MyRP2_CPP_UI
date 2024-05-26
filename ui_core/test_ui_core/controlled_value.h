#if !defined(CONTROLLED_VALUE_H)
#define CONTROLLED_VALUE_H

#include "ui_core.h"

class ControlledValue : public UIControlledIncrementalValue
{
private:
    std::string name;

public:
    ControlledValue(std::string _name, int _min_value = 0, int _max_value = 10, bool _is_wrapable = false, int increment = 1);
    ~ControlledValue();
    void process_control_event(ControlEvent _event);
    std::string get_name();
};

#endif // CONTROLLED_VALUE_H