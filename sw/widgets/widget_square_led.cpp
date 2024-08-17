#include "widget_square_led.h"

w_SquareLed::w_SquareLed(UIDisplayDevice *display_screen,
                         size_t width, size_t height,
                         uint8_t widget_anchor_x, uint8_t widget_anchor_y,
                         FramebufferColor color, FramebufferFormat framebuffer_format)
    : UIWidget(display_screen, width, height, widget_anchor_x, widget_anchor_y, true, 1, framebuffer_format)
{
}

w_SquareLed::~w_SquareLed()
{
}

void w_SquareLed::light_on()
{
    this->is_lit = true;
}

void w_SquareLed::light_off()
{
    this->is_lit = false;
}

void w_SquareLed::set_blink_us(uint32_t _blink_period)
{
    this->blink_period = _blink_period;
}

void w_SquareLed::blink_off()
{
    this->is_blinking = false;
}

void w_SquareLed::blink_on()
{
    this->is_blinking = true;
}
