add_library(widgets 
                    widget_square_led.cpp)   
target_link_libraries( widgets 
                    ui_core)  
                    
                    
add_executable(test_square_led
                    test_square_led.cpp)
target_link_libraries(test_square_led
                    ssd1306 
                    # pico_stdlib 
                    hardware_i2c 
                    # hw_i2c 
                    framebuffer
                    switch_button
                    widgets
                    )
pico_add_extra_outputs(test_square_led)