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
