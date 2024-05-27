#include "widget_print_serial_monitor.h"

WTextSerialMonitor::WTextSerialMonitor()
    : UIWidget(nullptr, 128, 8, 0, 0, false)
{
}

WTextSerialMonitor::~WTextSerialMonitor()
{
}

void WTextSerialMonitor::refresh()
{
    if (this->actual_displayed_object->has_changed())
    {
        draw();
        this->actual_displayed_object->clear_change_flag();
    }
}

void WTextSerialMonitor::set_displayed_object(ControlledValue *_new_displayed_object)
{
    this->set_displayed_model(_new_displayed_object);
    this->actual_displayed_object = _new_displayed_object;
}

void WTextSerialMonitor::draw()
{
    std::string text = "monitor: " + this->actual_displayed_object->get_name() + ":" + std::to_string(actual_displayed_object->get_value()) + "\n";
    printf(text.c_str());
}

void WCursorOnSerialMonitor::draw()
{
    int display_value = slope * actual_displayed_object->get_value() + offset;
    switch (actual_displayed_object->get_status())
    {
    case ControlledObjectStatus::WAITING:

        printf("[%s] is waiting\n", actual_displayed_object->get_name().c_str());
        break;
    case ControlledObjectStatus::HAS_FOCUS:
        printf("[%s] has focus\n", actual_displayed_object->get_name().c_str());
        break;
    case ControlledObjectStatus::IS_ACTIVE:
        printf("[%s] is active: %s %*c\n", actual_displayed_object->get_name().c_str(), std::to_string(actual_displayed_object->get_value()).c_str(), display_value, '|');
        break;
    default:
        break;
    }
}

WCursorOnSerialMonitor::WCursorOnSerialMonitor()
    : UIWidget(nullptr, 128, 8, 0, 0, false)
{
}

WCursorOnSerialMonitor::~WCursorOnSerialMonitor()
{
}

void WCursorOnSerialMonitor::refresh()
{
    if (this->actual_displayed_object->has_changed())
    {
        draw();
        this->actual_displayed_object->clear_change_flag();
    }
}

void WCursorOnSerialMonitor::set_displayed_object(ControlledValue *_actual_displayed_object)
{
    this->set_displayed_model(_actual_displayed_object);
    this->actual_displayed_object = _actual_displayed_object;
    slope = (max_line_width - 1.) / (actual_displayed_object->get_max_value() - actual_displayed_object->get_min_value());
    offset = 1 - slope * actual_displayed_object->get_min_value();
}
