#include "test_widget_on_serial_monitor.h"
#include <sstream>

std::map<ControlledObjectStatus, std::string> status_to_string{
    {ControlledObjectStatus::WAITING, "WAITING"},
    {ControlledObjectStatus::HAS_FOCUS, "HAS_FOCUS"},
    {ControlledObjectStatus::IS_ACTIVE, "IS_ACTIVE"}};

TestCursorWidgetWithIncrementalValue::TestCursorWidgetWithIncrementalValue()
    : UIWidget(nullptr, 128, 8, 0, 0, false)
{
}

TestCursorWidgetWithIncrementalValue::~TestCursorWidgetWithIncrementalValue()
{
}

void TestCursorWidgetWithIncrementalValue::refresh()
{
    if (this->actual_displayed_object->has_changed())
    {
        draw();
        this->actual_displayed_object->clear_change_flag();
    }
}

void TestCursorWidgetWithIncrementalValue::set_displayed_object(TestIncrementalValue *_actual_displayed_object)
{
    this->set_displayed_model(_actual_displayed_object);
    this->actual_displayed_object = _actual_displayed_object;

    slope = (max_line_width - 1.) / (actual_displayed_object->get_max_value() - actual_displayed_object->get_min_value());
    offset = 1 - slope * actual_displayed_object->get_min_value();
}

void TestCursorWidgetWithIncrementalValue::draw()
{
    // std::string text = "monitor: " + this->actual_displayed_object->get_name() + "[" + status_to_string[actual_displayed_object->get_status()] + "] :" + std::to_string(actual_displayed_object->get_value()) + "\n";
    // printf(text.c_str());
    int display_value = slope * actual_displayed_object->get_value() + offset;
    switch (actual_displayed_object->get_status())
    {
    case ControlledObjectStatus::WAITING:
        printf("[%s] is waiting with value[%d]\n", actual_displayed_object->get_name().c_str(), actual_displayed_object->get_value());
        break;
    case ControlledObjectStatus::HAS_FOCUS:
        printf("Focus on [%s] with value[%d]\n", actual_displayed_object->get_name().c_str(), actual_displayed_object->get_value());
        break;
    case ControlledObjectStatus::IS_ACTIVE:
        printf("[%s] is active: %s %*c\n", actual_displayed_object->get_name().c_str(), std::to_string(actual_displayed_object->get_value()).c_str(), display_value, '|');
        break;
    default:
        break;
    }
}

// void WCursorOnSerialMonitor::draw()
// {
//     int display_value = slope * actual_displayed_object->get_value() + offset;
//     switch (actual_displayed_object->get_status())
//     {
//     case ControlledObjectStatus::WAITING:

//         printf("[%s] is waiting\n", actual_displayed_object->get_name().c_str());
//         break;
//     case ControlledObjectStatus::HAS_FOCUS:
//         printf("[%s] has focus\n", actual_displayed_object->get_name().c_str());
//         break;
//     case ControlledObjectStatus::IS_ACTIVE:
//         printf("[%s] is active: %s %*c\n", actual_displayed_object->get_name().c_str(), std::to_string(actual_displayed_object->get_value()).c_str(), display_value, '|');
//         break;
//     default:
//         break;
//     }
// }

// WCursorOnSerialMonitor::WCursorOnSerialMonitor()
//     : UIWidget(nullptr, 128, 8, 0, 0, false)
// {
// }

// WCursorOnSerialMonitor::~WCursorOnSerialMonitor()
// {
// }

// void WCursorOnSerialMonitor::refresh()
// {
//     if (this->actual_displayed_object->has_changed())
//     {
//         draw();
//         this->actual_displayed_object->clear_change_flag();
//     }
// }

// void WCursorOnSerialMonitor::set_displayed_object(TestIncrementalValue *_actual_displayed_object)
// {
//     this->set_displayed_model(_actual_displayed_object);
//     this->actual_displayed_object = _actual_displayed_object;
//     slope = (max_line_width - 1.) / (actual_displayed_object->get_max_value() - actual_displayed_object->get_min_value());
//     offset = 1 - slope * actual_displayed_object->get_min_value();
// }

void TestObjectManagerWidget::draw()
{
    std::string text = "manager[" + status_to_string[actual_displayed_object->get_status()] + "] with value(" + std::to_string(actual_displayed_object->get_value()) + ")" + "\n";
    printf(text.c_str());
}

TestObjectManagerWidget::TestObjectManagerWidget()
    : UIWidget(nullptr, 128, 8, 0, 0, false)
{
}

TestObjectManagerWidget::~TestObjectManagerWidget()
{
}

void TestObjectManagerWidget::set_displayed_object(Test_Manager *_manager)
{
    this->set_displayed_model(_manager);
    this->actual_displayed_object = _manager;
}

void TestObjectManagerWidget::refresh()
{
    if (this->actual_displayed_object->has_changed())
    {
        draw();
        this->actual_displayed_object->clear_change_flag();
    }
}
