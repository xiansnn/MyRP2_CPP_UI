/**
 * @file test_manager.h
 * @author xiansnn (xiansnn@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#if !defined(TEST_MANAGER_H)
#define TEST_MANAGER_H

#include "ui_core.h"

class Test_Manager : public UIObjectManager
{
private:
public:
    Test_Manager(UIController * _controller);
    ~Test_Manager();
    void process_control_event(ControlEvent _event);
};




#endif // TEST_MANAGER_H
