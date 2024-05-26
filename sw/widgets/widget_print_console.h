#if !defined(WIDGET_PRINT_CONSOLE_H)
#define WIDGET_PRINT_CONSOLE_H

#include <string>

#include "ui_core.h"

class WTextSerialMonitor : public UIWidget
{
private:
    std::string text;
    void draw();
public:
    WTextSerialMonitor();
    ~WTextSerialMonitor();
    void set_text_to_display(std::string _text);
    void refresh();
};



#endif // WIDGET_PRINT_CONSOLE_H
