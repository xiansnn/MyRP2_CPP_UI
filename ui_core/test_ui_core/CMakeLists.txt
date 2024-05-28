
add_executable(test_ui_core 
                test_ui_core.cpp
                test_manager.cpp
                test_controlled_value.cpp
                )
target_link_libraries(test_ui_core 
                pico_stdlib
                rotary_encoder
                widget_print_serial_monitor
                debug_probe
                )
pico_add_extra_outputs(test_ui_core)