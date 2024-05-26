#include "widget_print_console.h"

WTextSerialMonitor::WTextSerialMonitor()
: UIWidget(nullptr,128,8,0,0,false)
{
}

WTextSerialMonitor::~WTextSerialMonitor()
{
}

void WTextSerialMonitor::set_text_to_display(std::string _text)
{
    this->text = _text;
}

void WTextSerialMonitor::refresh()
{
    if (this->displayed_object->has_changed())
    {
        draw();
        this->displayed_object->clear_change_flag();
    }

}

void WTextSerialMonitor::draw()
{
    printf(text.c_str());
}
