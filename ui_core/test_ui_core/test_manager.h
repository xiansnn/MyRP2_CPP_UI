#if !defined(TEST_MANAGER_H)
#define TEST_MANAGER_H

#include "ui_core.h"

class Test_Manager : public UIObjectManager
{
private:
public:
    Test_Manager(/* args */);
    ~Test_Manager();
    void process_control_event(ControlEvent _event);
};




#endif // TEST_MANAGER_H
