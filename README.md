# MyRP2_CPP_UI
This repository proposes a User Interface alternative version for RPi Pico.
All the classes defined here rely on the RPi Pico SDK version 1.5.1

## Complete documentation (still in construction)
Access to the the project web page with external browser [here](https://xiansnn.github.io/MyRP2_CPP_UI/).

Once open with browser, you will find doxygen documentation [here](docs\html\index.html)


## Motivation

I know that we can find lot of well defined and used UI interface e.g. Adafruit in Arduino environment, but the main motivation was first to have fun devoloping (quite) from scratch a user interface en C++.

The second motivation was to have a set of C++ classes that make development of Raspberry Pi Pico C++ application more friendly with a small UI with OLED display (the one I've got is the SSD1306 0.92").
Considering the time required to refresh the small OLED screen through the I2C link, I've consider that it will be worth thinking about something that refreshes parts of the screen only when data have been changed.
This is why I've started thinking about framebuffer and the way we can upload part of framebuffer to the display. I then developped C++ classes to handle SSD1306 and framebuffer.

## Background
During my professional period of activities, I've got knowledge about Model Based Engineering, Object Oriented Design, and Mathematical Abstractions in general. This is why I've based this development according to MVC design rules (Model View Control).

## Files organisation
The files directories have been inspired by the Pico SDK.
### "hw" directory
I'll place here C++ classes that abstract in some way the corresponding SDK functions related the HW peripheral of the Pico.
The first one is I2C.

### "sw" directory
The abstract clesses here are those related to SW helper. the first one is framebuffer. the next one will be widgets.

### "devices" directory
These are external components that I'll use.
The first one is "device_switch". This will be used to handle any kind of switches, either by IRQ or by cyclic sample. Deboucing is implemented. The device_switch is the good candidate to implement Controller part of MVC.
Derived from switch is the rotary encoder "device_KY0_40", a favorite device to built universal simple interface to choose menu, set value etc...
The first display is "device_SSD1306" as promised. MAy be others will come if I need them and I've time.

### "ui_core" directory
This where the abstract classes that provide UI facilities can be found. Together with a "test_ui_core" directory where a set of test program are developped : "test_controlled_value" as an exmaple of Model, "test_widget_on serial_monitor" as an exmaple of View, "device_KY_040" already mentionned above as example of Control and "test_manager" as example about how to manage several Model ans View with a single rotary encoder / switch as Control. 

### "utilities" directory
It contains a debug probe classe that can be useful to monitor what's going on the microcontroller thanks to level and pulse generated through some GPIO output.







