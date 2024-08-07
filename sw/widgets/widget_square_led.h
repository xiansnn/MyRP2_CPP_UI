#include "ui_core.h"

class w_SquareLed : public UIWidget
{
private:
    bool lit = true;
    bool blinking = false;
    uint32_t blink_period;

public:
    w_SquareLed(UIDisplayDevice *display_screen,
                size_t width,
                size_t height,
                uint8_t widget_anchor_x,
                uint8_t widget_anchor_y,
                FramebufferColor color = FramebufferColor::WHITE,
                FramebufferFormat framebuffer_format = FramebufferFormat::MONO_VLSB);
    ~w_SquareLed();

    void light_on();
    void light_off();
    void set_blink(uint32_t blink_period);
    void blink_off();

    void draw();
};
