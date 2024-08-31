#include "widget_square_led.h"

w_SquareLed::w_SquareLed(UIDisplayDevice *display_screen,
                         size_t width, size_t height,
                         uint8_t widget_anchor_x, uint8_t widget_anchor_y,
                         bool widget_with_border,
                         FramebufferColor color, FramebufferFormat framebuffer_format)
    : UIWidget(display_screen, width, height, widget_anchor_x, widget_anchor_y, widget_with_border, 1, framebuffer_format)
{
}

w_SquareLed::~w_SquareLed()
{
}

void w_SquareLed::light_on()
{
    this->led_is_on = true;
}

void w_SquareLed::light_off()
{
    this->led_is_on = false;
}

void w_SquareLed::widget_blink_refresh()
{
    if (this->led_is_blinking and this->blinking_phase_has_changed())
    {
        if (!led_is_on)
        {
            this->light_on();
            rect(widget_start_x, widget_start_y, widget_width, widget_height, true, FramebufferColor::WHITE);
            this->display_screen->show(this, this->widget_anchor_x, this->widget_anchor_y);
        }
        else
        {
            this->light_off();
            draw_border();
            rect(widget_start_x, widget_start_y, widget_width, widget_height, true, FramebufferColor::BLACK);
            this->display_screen->show(this, this->widget_anchor_x, this->widget_anchor_y);
        }
    }
}

void w_SquareLed::blink_off()
{
    this->led_is_blinking = false;
}

void w_SquareLed::blink_on()
{
    this->led_is_blinking = true;
}
