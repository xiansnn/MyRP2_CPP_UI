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
    bool is_lit = true;
    /**
     * @brief the blinking status of the led
     * 
     */
    bool is_blinking = false;
    /**
     * @brief the blinking period, in microseconds
     * 
     */
    uint32_t blink_period;
    

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
     * @brief Set the blink period in microseconds
     * 
     * @param blink_period 
     */
    void set_blink_us(uint32_t blink_period);
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
