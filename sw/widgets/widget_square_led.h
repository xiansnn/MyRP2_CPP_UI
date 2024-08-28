#include "ui_core.h"

/**
 * @brief A widget that show a square (it can be a rectangle) on the display.
 * 
 */
class w_SquareLed : public UIWidget
{
protected:
    /**
     * @brief the status of the led, on or off
     * 
     */
    bool led_is_on = true;
    /**
     * @brief the blinking status of the led
     * 
     */
    bool is_blinking = false;
    

public:
    /**
     * @brief Construct a new w SquareLed object
     * 
     * @param display_screen 
     * @param width 
     * @param height 
     * @param widget_anchor_x 
     * @param widget_anchor_y 
     * @param color 
     * @param framebuffer_format 
     */
    w_SquareLed(UIDisplayDevice *display_screen,
                size_t width,
                size_t height,
                uint8_t widget_anchor_x,
                uint8_t widget_anchor_y,
                FramebufferColor color = FramebufferColor::WHITE,
                FramebufferFormat framebuffer_format = FramebufferFormat::MONO_VLSB);
    ~w_SquareLed();

    /**
     * @brief set the led ON
     * 
     */
    void light_on();
    /**
     * @brief set the led OFF
     * 
     */
    void light_off();
    
    /**
     * @brief refresh the square led ON or OFF on blinking phase change
     * 
     */
    void blink_refresh();
    /**
     * @brief set the blinking of the led OFF
     * 
     */
    void blink_off();
    /**
     * @brief set the blinking of the led ON
     * 
     */
    void blink_on();




};
