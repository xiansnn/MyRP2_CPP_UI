add_subdirectory(framebuffer)
add_subdirectory(test_ui_core)
add_library( ui_core ui_core.cpp)
target_link_libraries(ui_core 
                        pico_stdlib 
                        framebuffer
                        )
                        