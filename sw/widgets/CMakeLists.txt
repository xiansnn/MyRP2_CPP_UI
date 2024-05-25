add_library(widget_print_console widget_print_console.cpp)
target_link_libraries(widget_print_console
                        pico_stdlib
                        ui_core
                        )