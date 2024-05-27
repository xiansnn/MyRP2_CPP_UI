add_library(widget_print_serial_monitor widget_print_serial_monitor.cpp)
target_link_libraries(widget_print_serial_monitor
                        pico_stdlib
                        ui_core
                        )